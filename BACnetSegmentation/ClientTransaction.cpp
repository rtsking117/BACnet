#include "ClientTransaction.h"

void CClientTransaction::SegmentTimerTimeout()
{
	switch(State)
	{
	case State_SegmentedRequest:
		if(SegmentRetryCount < Nretry)
		{
			++SegmentRetryCount;
			FillWindow(InitialSequenceNumber);
			StartSegmentTimer(Tseg);
			return;
		}
		//else fall through
	case State_SegmentedResponse:
		StopTimer(true);
		CompletePDUProcessing(BCE_ABORT_TSM_TIMEOUT);
		return;
	default:
		OutputDebugString(L"Timer went off in invalid state!");
		return;
	}
}

void CClientTransaction::RequestTimerTimeout()
{
	switch(State)
	{
	case State_AwaitResponse:
		StopTimer(true);
		if(RetryCount < Nretry)
		{
			++RetryCount;
			if(segs.IsSegmentedData())
			{
				SegmentRetryCount = 0;
				SentAllSegments = false;
				StartSegmentTimer(Tseg);
				InitialSequenceNumber = 0;
				ActualWindowSize = 1;
				U8 crhead[] = {
					((PDUType_ConfirmedRequest << 4) | 0x0E),
					(U8)((MaxSegmentsAllowed << 4) | MaxAPDUSize),
					InvokeID,
					0,
					ProposedWindowSize,
					ServiceChoice,
				};
				CObjectPtr<IBACnetTransmitBuffer> tx = CreateBACnetTransmitBuffer();
				CObjectPtr<IBACnetBuffer> buf = CreateBACnetBuffer(sizeof(crhead), crhead);
				tx->Push(segs.GetSegmentFromWindow(0));
				tx->Push(buf);
				State = State_SegmentedRequest;
				p->net->WriteAPDU(dest, tx, Message_WaitForTransmit | Message_ExpectingReply);
				return;
			}
			else
			{
				U8 crhead[] = {
					((PDUType_ConfirmedRequest << 4) | 0x02),
					(U8)((MaxSegmentsAllowed << 4) | MaxAPDUSize),
					InvokeID,
					ServiceChoice
				};
				CObjectPtr<IBACnetTransmitBuffer> tx = CreateBACnetTransmitBuffer();
				CObjectPtr<IBACnetBuffer> buf = CreateBACnetBuffer(sizeof(crhead), crhead);
				tx->Push(segs.GetSegmentFromWindow(0));
				tx->Push(buf);
				p->net->WriteAPDU(dest, tx, Message_WaitForTransmit | Message_ExpectingReply);
				StartRequestTimer(Tout);
				return;
			}
		}
		else
		{
			CompletePDUProcessing(BCE_ABORT_TSM_TIMEOUT);
		}
	}
}


void CClientTransaction::FillWindow(U8 SequenceNumber)
{
	U32 ix = 0;
	while(segs.IsWindowIndexValid(ix))
	{
		//send segments.
		U8 crhead[] = {
			((PDUType_ConfirmedRequest << 4) | 0x0E),
			(U8)(0x70 | MaxAPDUSize),
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
		((PDUType_ConfirmedRequest << 4) | 0x0A),
		(U8)(0x70 | MaxAPDUSize),
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

CClientTransaction::CClientTransaction(CObjectPtr<CSegmentAssembler> Parent, U8 InvokeId, CObjectPtr<IBACnetNetworkAddress> pDest):
	CTransaction(Parent,InvokeId,pDest)
{
}

CClientTransaction::~CClientTransaction()
{
}

BACnetResult CClientTransaction::StartClientTSM(U8 Service, MaxAPDU MaxAPDUSz, CObjectPtr<IBACnetBuffer> pAPDUBuffer)
{
	MaxAPDUSize = MaxAPDUSz;
	ServiceChoice = Service;
	if(pAPDUBuffer->GetSize() + 4 <= MaxAPDUTable[MaxAPDUSize])
	{
		//Unsegmented.
		RetryCount = 0;
		SentAllSegments = true;
		StartRequestTimer(Tout);
		U8 crhead[] = {
			((PDUType_ConfirmedRequest << 4) | 0x02),
			(U8)((MaxSegmentsAllowed << 4) | MaxAPDUSize),
			InvokeID,
			ServiceChoice
		};
		segs.PushSegment(pAPDUBuffer);
		CObjectPtr<IBACnetTransmitBuffer> tx = CreateBACnetTransmitBuffer();
		CObjectPtr<IBACnetBuffer> buf = CreateBACnetBuffer(sizeof(crhead), crhead);
		tx->Push(segs.GetSegmentFromWindow(0));
		tx->Push(buf);
		State = State_AwaitResponse;
		return p->net->WriteAPDU(dest, tx, Message_WaitForTransmit | Message_ExpectingReply);
	}
	else
	{
		//Segmented.
		if(MaxSegmentsAllowed == MaxSeg_Unspecified)
		{
			//Not allowed!
			State = State_Complete;
			return BCE_ABORT_APDU_TOO_LONG;
		}
		U32 sz = pAPDUBuffer->GetSize();
		while(sz)
		{
			U32 readsz = min(sz, (U32)(MaxAPDUTable[MaxAPDUSize] - 6));
			CObjectPtr<IBACnetBuffer> b = CreateBACnetBuffer(readsz);
			pAPDUBuffer->Read(readsz, b);
			segs.PushSegment(b);
			sz -= readsz;
		}
		if(((U32)(1 << MaxSegmentsAllowed)) < segs.GetNumSegments())
		{
			State = State_Complete;
			return BCE_ABORT_APDU_TOO_LONG;
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
			((PDUType_ConfirmedRequest << 4) | 0x0E),
			(U8)((MaxSegmentsAllowed << 4) | MaxAPDUSize),
			InvokeID,
			0,
			ProposedWindowSize,
			ServiceChoice,
		};
		CObjectPtr<IBACnetTransmitBuffer> tx = CreateBACnetTransmitBuffer();
		CObjectPtr<IBACnetBuffer> buf = CreateBACnetBuffer(sizeof(crhead), crhead);
		tx->Push(segs.GetSegmentFromWindow(0));
		tx->Push(buf);
		State = State_SegmentedRequest;
		return p->net->WriteAPDU(dest, tx, Message_WaitForTransmit | Message_ExpectingReply);
	}
}

BACnetResult CClientTransaction::OnConfirmedRequest(U8 PDUType, U8 PDUFlags, U8 SequenceNumber, U8 ProposedWindowSize, U8 ServiceChoice, CObjectPtr<IBACnetBuffer> pBuffer)
{
	//client requests cannot receive confirmed requests.
	return Abort(Abort_InvalidAPDUInThisState);
}

BACnetResult CClientTransaction::OnSegmentAck(U8 PDUType, U8 SequenceNumber, U8 ActualWindowSz)
{
	switch(State)
	{
	case State_SegmentedRequest:
		if(!(PDUType & PDUFlag_IsServer))
		{
			//Abort - got a client ack to a client request.
			return Abort(Abort_InvalidAPDUInThisState);
		}
		if(InWindow(SequenceNumber, InitialSequenceNumber))
		{
			if(SentAllSegments)
			{
				//Final Ack. 
				StopTimer();
				StartRequestTimer(Tout);
				State = State_AwaitResponse;
				return BC_OK;
			}
			else
			{
				//New Ack
				StopTimer();
				segs.ShiftSegmentWindow((SequenceNumber - InitialSequenceNumber) + 1);
				InitialSequenceNumber = (SequenceNumber + 1) & 0xFF;
				ActualWindowSize = ActualWindowSz;
				SegmentRetryCount = 0;
				FillWindow(InitialSequenceNumber);
				StartSegmentTimer(Tseg);
				return BC_OK;
			}
		}
		else
		{
			//duplicate
			ResetTimer(Tseg);
			return BC_OK;
		}
	case State_SegmentedResponse:
	case State_AwaitResponse:
	case State_Complete:
		//drop it.
		return BC_OK;
	case State_Idle:
		return Abort(Abort_InvalidAPDUInThisState);
		BACNET_UNREACHABLECASE;
	}
}

BACnetResult CClientTransaction::OnComplexAck(U8 PDUType, U8 SequenceNumber, U8 ProposedWindowSize, CObjectPtr<IBACnetBuffer> pBuffer)
{
	switch(State)
	{
	case State_Idle:
		if(PDUType & PDUFlag_IsSegmented)
		{
			return Abort(Abort_InvalidAPDUInThisState);
		}
		return BC_OK;
	case State_AwaitResponse:
	case State_SegmentedRequest:
		if((State == State_SegmentedRequest && SentAllSegments == false) || ((PDUType & PDUFlag_IsSegmented) && (SequenceNumber != 0)))
		{
			return Abort(Abort_InvalidAPDUInThisState);
		}
		StopTimer();
		segs.EmptySegmentBuffer();	
		segs.PushSegment(pBuffer);
		if(!(PDUType & PDUFlag_IsSegmented))
		{
			return CompletePDUProcessing();
		}
		else
		{
			ActualWindowSize = min(16, ProposedWindowSize);
			BACnetResult r = SendSegmentAck(false);
			StartSegmentTimer(Tsegwait);
			LastSequenceNumber = 0;
			InitialSequenceNumber = 0;
			DuplicateCount = 0;
			State = State_SegmentedResponse;
			return r;
		}
	case State_SegmentedResponse:
		if(!(PDUType & PDUFlag_IsSegmented))
		{
			return Abort(Abort_InvalidAPDUInThisState);
		}
		if(SequenceNumber != ((LastSequenceNumber + 1) & 0xFF))
		{
			if(DuplicateInWindow(SequenceNumber, ((InitialSequenceNumber + 1) & 0xFF), LastSequenceNumber))
			{
				//duplicate.
				BACnetResult r = BC_OK;
				if(DuplicateCount >= ActualWindowSize)
				{
					//Too many duplicates.
					DuplicateCount = 0;
					r = SendSegmentAck(false, true);
				}
				else
				{
					++DuplicateCount;
				}
				ResetTimer(Tsegwait);
				return r;
			}
			else
			{
				//segment out of order.
				InitialSequenceNumber = LastSequenceNumber;
				DuplicateCount = 0;
				BACnetResult r = SendSegmentAck(false,true);
				ResetTimer(Tsegwait);
				return r;
			}
		}
		//its one in the sequence.
		if(!(PDUType & PDUFlag_MoreFollows))
		{
			//final segment.
			StopTimer();
			segs.PushSegment(pBuffer);
			SendSegmentAck(false);
			return CompletePDUProcessing();
		}
		else
		{
			//new segment.
			segs.PushSegment(pBuffer);
			LastSequenceNumber = (LastSequenceNumber + 1) & 0xFF;
			if(SequenceNumber == ((InitialSequenceNumber + ActualWindowSize) & 0xFF))
			{
				InitialSequenceNumber = LastSequenceNumber;
				DuplicateCount = 0;
				SendSegmentAck(false);
			}
			ResetTimer(Tsegwait);
		}
		return BC_OK;
	case State_Complete:
		return BC_OK;
		BACNET_UNREACHABLECASE;
	}
}

BACnetResult CClientTransaction::OnSimpleAck()
{
	switch(State)
	{
	case State_SegmentedRequest:
	case State_AwaitResponse:
		if(SentAllSegments == true)
		{
			StopTimer();
			segs.EmptySegmentBuffer();
			return CompletePDUProcessing();
		}
	default:
		return Abort(Abort_InvalidAPDUInThisState);
	}
}

BACnetResult CClientTransaction::OnAbort(bool isServer, AbortCode reason)
{
	if(!isServer)
	{
		return BCE_INVALID_OPERATION;
	}
	switch(State)
	{
	case State_SegmentedRequest:
	case State_SegmentedResponse:
	case State_AwaitResponse:
		StopTimer();
		return CompletePDUProcessing(BCNRESULT_FROM_ABORT(reason));
	case State_Idle:
	case State_Complete:
		//drop it on complete.
		return BC_OK;
		BACNET_UNREACHABLECASE;
	}
}

BACnetResult CClientTransaction::OnReject(RejectCode reason)
{
	switch(State)
	{
	case State_Idle:
	case State_Complete:
		return BC_OK;
	case State_SegmentedRequest:
	case State_AwaitResponse:
		StopTimer();
		return CompletePDUProcessing(BCNRESULT_FROM_REJECT(reason));
	case State_SegmentedResponse:
		return Abort(Abort_InvalidAPDUInThisState);
		BACNET_UNREACHABLECASE;
	}
}

BACnetResult CClientTransaction::OnError(CObjectPtr<IBACnetBuffer> pEncodedError)
{
	switch(State)
	{
	case State_Idle:
	case State_Complete:
		return BC_OK;
	case State_SegmentedRequest:
	case State_AwaitResponse:
		StopTimer();
		if(SentAllSegments == true)
		{
			segs.EmptySegmentBuffer();
			segs.PushSegment(pEncodedError);
			return CompletePDUProcessing(BCE_BACNET_ERROR_CODE);
		}
		//else fall through
	case State_SegmentedResponse:
		return Abort(Abort_InvalidAPDUInThisState);
		BACNET_UNREACHABLECASE;
	}
}

BACnetResult CClientTransaction::Acknowledge(CObjectPtr<IBACnetBuffer> pResponseData)
{
	//clients are sending requests, not recieving them.
	return BCE_INVALID_OPERATION;
}

BACnetResult CClientTransaction::Abort(AbortCode Reason)
{
	if(State != State_Complete)
	{
		U8 abtheader[] = {
			(PDUType_Abort << 4),
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

BACnetResult CClientTransaction::Reject(RejectCode Reason)
{
	//only a server can send a reject.
	return BCE_INVALID_OPERATION;
}

BACnetResult CClientTransaction::SendError(CObjectPtr<IBACnetBuffer> pEncodedError)
{
	//only a server can send an error.
	return BCE_INVALID_OPERATION;
}

