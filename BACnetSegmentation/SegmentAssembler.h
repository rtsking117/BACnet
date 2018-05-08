#pragma once
#include "ComWrapper.h"
#include <map>
#include <set>
#include <vector>
#include <memory>
#include <Windows.h>

class CSegmentAssembler;

#include "TransactionSet.h"

class CSegmentAssembler :
	public ComWrapper<IBACnetTransactionManager>
{
	UnconfirmedRequestHandler OnUnconfirmedRequest;
public:
	ConfirmedRequestHandler OnConfirmedRequest;
	CObjectPtr<IBACnetNetwork> net;
private:
	CObjectPtr<TransactionSet> activetrx;
public:
	MaxSegments MaxSegmentsAllowed;
private:
	U8 LastInstanceID;
	bool live;

	U8 GetNextInstanceID();
	BACnetResult ProcessAPDU(CObjectPtr<IBACnetNetworkAddress> pAddr, CObjectPtr<IBACnetBuffer> msg);
	CObjectPtr<CTransaction> CreateServerTransaction(U8 InvokeID, CObjectPtr<IBACnetNetworkAddress> pDest);
	CObjectPtr<CTransaction> CreateClientTransaction(U8 InvokeID, CObjectPtr<IBACnetNetworkAddress> pDest, U8 ServiceChoice, MaxAPDU MaxAPDUSize, CObjectPtr<IBACnetBuffer> tx);

public:
	CSegmentAssembler(U16 MaxSegments);
	~CSegmentAssembler();

	//IBACnetStackComponent
	 BACnetResult BACNETMETHODCALLTYPE Start();
	 BACnetResult BACNETMETHODCALLTYPE Stop();

	//IBACnetTransactionManager
	BACnetResult BACNETMETHODCALLTYPE AttachNetwork(CObjectPtr<IBACnetNetwork> pNetwork);
	CObjectPtr<IBACnetNetwork> BACNETMETHODCALLTYPE GetNetwork() const;
	BACnetResult BACNETMETHODCALLTYPE DetachNetwork();
	BACnetResult BACNETMETHODCALLTYPE RegisterConfirmedRequestHandler(ConfirmedRequestHandler pHandler);
	BACnetResult BACNETMETHODCALLTYPE RemoveConfirmedRequestHandler();
	BACnetResult BACNETMETHODCALLTYPE RegisterUnconfirmedRequestHandler(UnconfirmedRequestHandler pHandler);
	BACnetResult BACNETMETHODCALLTYPE RemoveUnconfirmedRequestHandler();
	BACnetResult BACNETMETHODCALLTYPE SendConfirmedRequest(CObjectPtr<IBACnetNetworkAddress> pDestination, U8 ServiceChoice, CObjectPtr<IBACnetBuffer> pMessage, CObjectPtr<IBACnetTransaction>& pTransaction);
	BACnetResult BACNETMETHODCALLTYPE SendUnconfirmedRequest(CObjectPtr<IBACnetNetworkAddress> pDestination, U8 ServiceChoice, CObjectPtr<IBACnetBuffer> pMessage) const;
	
	BACnetResult RemoveTransaction(CObjectPtr<CTransaction> trx);
};

