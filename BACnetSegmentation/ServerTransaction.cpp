#include "ServerTransaction.h"

void CServerTransaction::SegmentTimerTimeout()
{
	switch(State)
	{
	case State_SegmentedResponse:
		if(SegmentRetryCount < Nretry)
		{
			++SegmentRetryCount;
			FillWindow(InitialSequenceNumber);
			ResetTimer(Tseg);
			return;
		}
		StopTimer(true);
	case State_SegmentedRequest:
		CompletePDUProcessing(BCE_ABORT_TSM_TIMEOUT);
	case State_Idle:
	case State_Complete:
	case State_AwaitResponse:
		return;
	}
}

void CServerTransaction::RequestTimerTimeout()
{
	switch(State)
	{
	case State_Idle:
	case State_Complete:
	case State_SegmentedResponse:
	case State_SegmentedRequest:
		return;
	case State_AwaitResponse:
		Abort(Abort_ApplicationExceededReplyTime);
	}
}

void CServerTransaction::FillWindow(U8 SequenceNumber)
{
	U32 ix = 0;
	while(segs.IsWindowIndexValid(ix))
	{
		//send segments.
		U8 crhead[] = {
			((PDUType_ComplexAck << 4) | 0x0C),
			InvokeID,
			((SequenceNumber + ix) & 0xFF),
			ProposedWindowSize,
			ServiceChoice,
		};
		CObjectPtr<IBACnetTransmitBuffer> tx = CreateBACnetTransmitBuffer();
		CObjectPtr<IBACnetBuffer> buf = CreateBACnetBuffer(sizeof(crhead), crhead);
		tx->Push(segs.GetSegmentFromWindow(ix));
		tx->Push(buf);
		p->net->WriteAPDU(dest, tx, Message_WaitForTransmit | Message_ExpectingReply);
		//and end
		++ix;
		if(ix >= ActualWindowSize)
		{
			return;
		}
	}
	//Send last segment.
	U8 crhead[] = {
		((PDUType_ComplexAck << 4) | 0x08),
		InvokeID,
		((SequenceNumber + ix) & 0xFF),
		ProposedWindowSize,
		ServiceChoice,
	};
	CObjectPtr<IBACnetTransmitBuffer> tx = CreateBACnetTransmitBuffer();
	CObjectPtr<IBACnetBuffer> buf = CreateBACnetBuffer(sizeof(crhead), crhead);
	tx->Push(segs.GetSegmentFromWindow(ix));
	tx->Push(buf);
	p->net->WriteAPDU(dest, tx, Message_WaitForTransmit | Message_ExpectingReply);
	SentAllSegments = true;
}

CServerTransaction::CServerTransaction(CObjectPtr<CSegmentAssembler> Parent, U8 InvokeID, CObjectPtr<IBACnetNetworkAddress> pDest) :
	CTransaction(Parent, InvokeID, pDest),
	MaxSegmentsSupported(MaxSeg_Unspecified),
	AllowSegmentedResponse(true)
{
}

CServerTransaction::~CServerTransaction()
{
}

BACnetResult CServerTransaction::StartServerTSM()
{
	State = State_Idle;
	return BC_OK;
}

BACnetResult CServerTransaction::Acknowledge(CObjectPtr<IBACnetBuffer> pResponseData)
{
	StopTimer();
	if(pResponseData)
	{
		//complex ack.
		if(pResponseData->GetSize() + 3 <= MaxAPDUTable[MaxAPDUSize])
		{
			//Unsegmented.
			U8 crhead[] = {
				((PDUType_ComplexAck << 4)),
				InvokeID,
				ServiceChoice
			};
			segs.PushSegment(pResponseData);
			CObjectPtr<IBACnetTransmitBuffer> tx = CreateBACnetTransmitBuffer();
			pResponseData = CreateBACnetBuffer(sizeof(crhead), crhead);
			tx->Push(segs.GetSegmentFromWindow(0));
			tx->Push(pResponseData);
			p->net->WriteAPDU(dest, tx, Message_WaitForTransmit);
			return CompletePDUProcessing();
		}
		else
		{
			//Segmented.
			if(!AllowSegmentedResponse)
			{
				Abort(Abort_SegmentationNotSupported);
				return BCE_ABORT_SEGMENTATION_NOT_SUPPORTED;
			}
			U32 sz = pResponseData->GetSize();
			while(sz)
			{
				U32 readsz = min(sz, (U32)(MaxAPDUTable[MaxAPDUSize] - 5));
				CObjectPtr<IBACnetBuffer> b = nullptr;
				pResponseData->Read(readsz, b);
				segs.PushSegment(b);
				sz -= readsz;
			}
			if((((U32)(1 << MaxSegmentsAllowed)) < segs.GetNumSegments()) ||
				(((U32)(1 << MaxSegmentsSupported)) < segs.GetNumSegments()))
			{
				Abort(Abort_BufferOverflow);
				return BCE_ABORT_BUFFER_OVERFLOW;
			}
			//send the first segment.
			RetryCount = 0;
			SegmentRetryCount = 0;
			InitialSequenceNumber = 0;
			ProposedWindowSize = 16;
			ActualWindowSize = 1;
			SentAllSegments = false;
			StartSegmentTimer(Tseg);
			U8 crhead[] = {
				((PDUType_ComplexAck << 4) | 0x0C),
				InvokeID,
				InitialSequenceNumber,
				ProposedWindowSize,
				ServiceChoice,
			};
			CObjectPtr<IBACnetTransmitBuffer> tx = CreateBACnetTransmitBuffer();
			pResponseData = CreateBACnetBuffer(sizeof(crhead), crhead);
			tx->Push(segs.GetSegmentFromWindow(InitialSequenceNumber));
			tx->Push(pResponseData);
			State = State_SegmentedRequest;
			return p->net->WriteAPDU(dest, tx, Message_WaitForTransmit | Message_ExpectingReply);
		}
	}
	else
	{
		//simple ack.
		U8 abtheader[] = {
			(PDUType_SimpleAck << 4),
			InvokeID,
			ServiceChoice,
		};
		StopTimer();
		pResponseData = CreateBACnetBuffer(sizeof(abtheader), abtheader);
		CObjectPtr<IBACnetTransmitBuffer> tx = CreateBACnetTransmitBuffer();
		tx->Push(pResponseData);
		p->net->WriteAPDU(dest, tx, Message_WaitForTransmit);
		return CompletePDUProcessing();
	}
}

BACnetResult CServerTransaction::Abort(AbortCode Reason)
{
	if(State != State_Complete)
	{
		U8 abtheader[] = {
			(PDUType_Abort << 4) | 0x01,
			InvokeID,
			(U8)Reason,
		};
		StopTimer();
		CObjectPtr<IBACnetBuffer> b = CreateBACnetBuffer(sizeof(abtheader), abtheader);
		CObjectPtr<IBACnetTransmitBuffer> tx = CreateBACnetTransmitBuffer();
		tx->Push(b);
		p->net->WriteAPDU(dest, tx, Message_WaitForTransmit);
		return CompletePDUProcessing(BCNRESULT_FROM_ABORT(Reason));
	}
	return BCE_INVALID_OPERATION;
}

BACnetResult CServerTransaction::Reject(RejectCode Reason)
{
	if(State == State_AwaitResponse)
	{
		U8 abtheader[] = {
			(PDUType_Reject << 4) | 0x01,
			InvokeID,
			(U8)Reason,
		};
		StopTimer();
		CObjectPtr<IBACnetBuffer> b = CreateBACnetBuffer(sizeof(abtheader), abtheader);
		CObjectPtr<IBACnetTransmitBuffer> tx = CreateBACnetTransmitBuffer();
		tx->Push(b);
		p->net->WriteAPDU(dest, tx, Message_WaitForTransmit);
		return CompletePDUProcessing(BCNRESULT_FROM_REJECT(Reason));
	}
	return BCE_INVALID_OPERATION;
}

BACnetResult CServerTransaction::SendError(CObjectPtr<IBACnetBuffer> pEncodedError)
{
	if(State == State_AwaitResponse)
	{
		U8 abtheader[] = {
			(PDUType_Error << 4) | 0x01,
			InvokeID,
			ServiceChoice,
		};
		StopTimer();
		CObjectPtr<IBACnetBuffer> b = CreateBACnetBuffer(sizeof(abtheader), abtheader);
		CObjectPtr<IBACnetTransmitBuffer> tx = CreateBACnetTransmitBuffer();
		tx->Push(pEncodedError);
		tx->Push(b);
		p->net->WriteAPDU(dest, tx, Message_WaitForTransmit);
		return CompletePDUProcessing(BCE_BACNET_ERROR_CODE);
	}
	return BCE_INVALID_OPERATION;
}

BACnetResult CServerTransaction::OnConfirmedRequest(U8 PDUType, U8 PDUFlags, U8 SequenceNumber, U8 ProposedWindowSize, U8 ServiceChoice, CObjectPtr<IBACnetBuffer> pBuffer)
{
	switch(State)
	{
	case State_Idle:
		if(PDUType & PDUFlag_IsSegmented)
		{
			if(SequenceNumber != 0)
			{
				return Abort(Abort_InvalidAPDUInThisState);
			}
			if(ProposedWindowSize == 0 || ProposedWindowSize > 127)
			{
				return Abort(Abort_WindowSizeOutOfRange);
			}
			this->ServiceChoice = ServiceChoice;
			MaxSegmentsSupported = (MaxSegments)((PDUFlags & 0x70) >> 4);
			MaxAPDUSize = (MaxAPDU)((PDUFlags & 0x0F));
			segs.PushSegment(pBuffer);
			ActualWindowSize = min(16, ProposedWindowSize);
			SendSegmentAck(true);
			StartSegmentTimer(Tsegwait);
			LastSequenceNumber = InitialSequenceNumber = DuplicateCount = 0;
			State = State_SegmentedRequest;
			return BC_OK;
		}
		else
		{
			segs.PushSegment(pBuffer);
			State = State_AwaitResponse;
			this->ServiceChoice = ServiceChoice;
			AllowSegmentedResponse = PDUType & PDUFlag_SegmentResponse ? true : false;
			MaxSegmentsSupported = (MaxSegments)((PDUFlags & 0x70) >> 4);
			MaxAPDUSize = (MaxAPDU)((PDUFlags & 0x0F));
			StartRequestTimer(Tout);
			BACnetResult r = p->OnConfirmedRequest(this);
			return CompletePDUProcessing(r);
		}
	case State_SegmentedRequest:
		if(!(PDUType & PDUFlag_IsSegmented))
		{
			return Abort(Abort_InvalidAPDUInThisState);
		}
		if(SequenceNumber != ((LastSequenceNumber + 1) & 0xFF))
		{
			if(DuplicateInWindow(SequenceNumber, ((InitialSequenceNumber + 1) & 0xFF), LastSequenceNumber) && DuplicateCount < ActualWindowSize)
			{
				ResetTimer(Tsegwait);
				++DuplicateCount;
				return BC_OK;
			}
			SendSegmentAck(true, true);
			ResetTimer(Tsegwait);
			InitialSequenceNumber = LastSequenceNumber;
			DuplicateCount = 0;
			return BC_OK;
		}
		segs.PushSegment(pBuffer);
		LastSequenceNumber = ((LastSequenceNumber + 1) & 0xFF);
		if(PDUType & PDUFlag_MoreFollows)
		{
			if(SequenceNumber != ((InitialSequenceNumber + ActualWindowSize) & 0xFF))
			{
				//new seg
				ResetTimer(Tsegwait);
				return BC_OK;
			}
			else
			{
				//last seg of group.
				SendSegmentAck(true);
				ResetTimer(Tsegwait);
				InitialSequenceNumber = LastSequenceNumber;
				DuplicateCount = 0;
				return BC_OK;
			}
		}
		else
		{
			StopTimer();
			SendSegmentAck(true);
			ResetTimer(Tsegwait);
			InitialSequenceNumber = LastSequenceNumber;
			State = State_AwaitResponse;
			StartRequestTimer(Tout);
			BACnetResult r = p->OnConfirmedRequest(this);
			return CompletePDUProcessing(r);
		}
	case State_AwaitResponse:
		if(PDUType & PDUFlag_IsSegmented)
		{
			return SendSegmentAck(true, true);
		}
		return BC_OK;
	case State_SegmentedResponse:
		return Abort(Abort_InvalidAPDUInThisState);
	case State_Complete:
		return BC_OK;
		BACNET_UNREACHABLECASE;
	}
}

BACnetResult CServerTransaction::OnSegmentAck(U8 PDUType, U8 SequenceNumber, U8 ActualWindowSz)
{
	switch(State)
	{
	case State_Idle:
	case State_SegmentedRequest:
	case State_AwaitResponse:
		return Abort(Abort_InvalidAPDUInThisState);
	case State_SegmentedResponse:
		if(InWindow(SequenceNumber, InitialSequenceNumber))
		{
			if(SentAllSegments)
			{
				StopTimer();
				return BC_OK;
			}
			InitialSequenceNumber = ((SequenceNumber + 1) & 0xFF);
			ActualWindowSize = ActualWindowSz;
			SegmentRetryCount = 0;
			FillWindow(InitialSequenceNumber);
		}
		ResetTimer(Tseg);
		return BC_OK;
	case State_Complete:
		return BC_OK;
		BACNET_UNREACHABLECASE;
	}
}

BACnetResult CServerTransaction::OnComplexAck(U8 PDUType, U8 SequenceNumber, U8 ProposedWindowSize, CObjectPtr<IBACnetBuffer> pBuffer)
{
	return BC_OK;
}

BACnetResult CServerTransaction::OnSimpleAck()
{
	return BC_OK;
}

BACnetResult CServerTransaction::OnAbort(bool isServer, AbortCode reason)
{
	switch(State)
	{
	case State_Idle:
	case State_Complete:
		return BC_OK;
	case State_SegmentedRequest:
	case State_AwaitResponse:
	case State_SegmentedResponse:
		StopTimer();
		return CompletePDUProcessing(BCNRESULT_FROM_ABORT(reason));
		BACNET_UNREACHABLECASE;
	}
}

BACnetResult CServerTransaction::OnReject(RejectCode reason)
{
	return BC_OK;
}

BACnetResult CServerTransaction::OnError(CObjectPtr<IBACnetBuffer> pEncodedError)
{
	return BC_OK;
}
