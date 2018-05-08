#pragma once

#include "Transaction.h"

class CClientTransaction :
	public CTransaction
{
	void SegmentTimerTimeout();
	void RequestTimerTimeout();
	
	void FillWindow(U8 SequenceNumber);
public:
	CClientTransaction(CObjectPtr<CSegmentAssembler> Parent, U8 InvokeID, CObjectPtr<IBACnetNetworkAddress> pDest);
	~CClientTransaction();

	BACnetResult StartClientTSM(U8 ServiceChoice, MaxAPDU MaxAPDUSize, CObjectPtr<IBACnetBuffer> pAPDUBuffer);
	//IBACnetTransaction
	BACnetResult BACNETMETHODCALLTYPE Acknowledge(CObjectPtr<IBACnetBuffer> pResponseData = nullptr);
	BACnetResult BACNETMETHODCALLTYPE Abort(AbortCode Reason);
	BACnetResult BACNETMETHODCALLTYPE Reject(RejectCode Reason);
	BACnetResult BACNETMETHODCALLTYPE SendError(CObjectPtr<IBACnetBuffer> pEncodedError);
	//CTransaction
	BACnetResult OnConfirmedRequest(U8 PDUType, U8 PDUFlags, U8 SequenceNumber, U8 ProposedWindowSize, U8 ServiceChoice, CObjectPtr<IBACnetBuffer> pBuffer);
	BACnetResult OnSegmentAck(U8 PDUType, U8 SequenceNumber, U8 ActualWindowSize);
	BACnetResult OnComplexAck(U8 PDUType, U8 SequenceNumber, U8 ProposedWindowSize, CObjectPtr<IBACnetBuffer> pBuffer);
	BACnetResult OnSimpleAck();
	BACnetResult OnAbort(bool isServer, AbortCode reason);
	BACnetResult OnReject(RejectCode reason);
	BACnetResult OnError(CObjectPtr<IBACnetBuffer> pEncodedError);
};

