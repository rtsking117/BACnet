#pragma once
#include <ObjectWrapper.h>
#include "APCI.h"
#include <Windows.h>
#include "SegmentBuffer.h"

class CTransaction;

#include "SegmentAssembler.h"

enum TSMState
{
	//Common states
	State_Idle,
	State_SegmentedRequest,
	State_AwaitResponse,
	State_SegmentedResponse,
	State_Complete,
};

class CTransaction :
	public ObjectWrapper<IBACnetTransaction>
{
protected:
	CSegmentBuffer segs;
	CObjectPtr<CSegmentAssembler> p;
	CObjectPtr<IBACnetNetworkAddress> dest;
private:
	CObjectPtr<IBACnetEvent> pEvent;
	CObjectPtr<IBACnetThreadpoolTimer> Timer;
	BACnetResult ResultCode;
protected:
	U32 RetryCount;
	U32 SegmentRetryCount;
	U32 DuplicateCount;
	U32 Tseg;
	U32 Tsegwait;
	U32 Tout;
	U32 Nretry;
	U8 LastSequenceNumber;
	U8 InitialSequenceNumber;
	U8 ActualWindowSize;
	U8 ProposedWindowSize;
	U8 InvokeID;
	U8 ServiceChoice;
	TSMState State;
	MaxAPDU MaxAPDUSize;
	MaxSegments MaxSegmentsAllowed;
	bool SentAllSegments;

private:
	bool segwait;
	BACnetResult OnTimerExpired(CObjectPtr<IBACnetThreadpool> pThreadpool, CallbackHandle pHandle, CObjectPtr<IBACnetThreadpoolTimer> pTimer);

protected:
	void StartRequestTimer(U32 Timeout);
	void StartSegmentTimer(U32 Timeout);
	void StopTimer(bool DontBlock = false);
	void ResetTimer(U32 Timeout);


	bool InWindow(U8 SeqNumA, U8 SeqNumB);

	bool DuplicateInWindow(U8 SeqNumA, U8 FirstSeqNum, U8 LastSeqNum);

	virtual void RequestTimerTimeout() = 0;
	virtual void SegmentTimerTimeout() = 0;

	BACnetResult SendSegmentAck(bool IsServer, bool IsNAK = false);

	BACnetResult CompletePDUProcessing(BACnetResult ReturnCode = BC_OK);

public:
	CTransaction(CObjectPtr<CSegmentAssembler> Parent, U8 InvokeId, CObjectPtr<IBACnetNetworkAddress> pDest);
	virtual ~CTransaction();

	U8 GetInvokeID();

	CObjectPtr<IBACnetNetworkAddress> BACNETMETHODCALLTYPE GetSender() const;
	U8 BACNETMETHODCALLTYPE GetServiceChoice() const;
	BACnetResult BACNETMETHODCALLTYPE WaitForCompletion();
	BACnetResult BACNETMETHODCALLTYPE GetTransactionResult() const;
	CObjectPtr<IBACnetBuffer> BACNETMETHODCALLTYPE GetTransactionData();
	
	virtual BACnetResult OnConfirmedRequest(U8 PDUType, U8 PDUFlags, U8 SequenceNumber, U8 ProposedWindowSize, U8 ServiceChoice, CObjectPtr<IBACnetBuffer> pBuffer) = 0;
	virtual BACnetResult OnSegmentAck(U8 PDUType, U8 SequenceNumber, U8 ActualWindowSize) = 0;
	virtual BACnetResult OnComplexAck(U8 PDUType, U8 SequenceNumber, U8 ProposedWindowSize, CObjectPtr<IBACnetBuffer> pBuffer) = 0;
	virtual BACnetResult OnSimpleAck() = 0;
	virtual BACnetResult OnAbort(bool isServer, AbortCode reason) = 0;
	virtual BACnetResult OnReject(RejectCode reason) = 0;
	virtual BACnetResult OnError(CObjectPtr<IBACnetBuffer> pEncodedError) = 0;
};

