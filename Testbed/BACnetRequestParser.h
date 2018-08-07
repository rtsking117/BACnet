#pragma once

#include <ObjectWrapper.h>
#include <BACnetApplication.h>

typedef std::function<BACnetResult(U8, bool, BACnetValue&)> DisplayCallback;

class BACnetRequestParser :
	public ObjectWrapper<IBACnetUnknown>
{
	CObjectPtr<IBACnetTransactionManager> tsm;
	DisplayCallback DisplayCallbackFunction;
	BACnetObjectID DeviceID;
	bool live;

	BACnetResult OnConfirmedRequest(CObjectPtr<IBACnetTransaction> tx);
	BACnetResult OnUnconfirmedRequest(CObjectPtr<IBACnetNetworkAddress> src, U8 svc, CObjectPtr<IBACnetBuffer> msg);

public:
	BACnetRequestParser();
	~BACnetRequestParser();

	//IBACnetStackComponent
	BACnetResult Start();
	BACnetResult Stop();
	//IBACnetApplication
	BACnetResult AttachTransactionManager(CObjectPtr<IBACnetTransactionManager> pTransactionManager);
	CObjectPtr<IBACnetTransactionManager> GetTransactionManager();
	BACnetResult DetachTransactionManager(void);
	//IBACnetRequestParser
	BACnetResult RegisterPreliminaryDisplayCallback(DisplayCallback pCallback);
};

CObjectPtr<BACnetRequestParser> CreateRequestParser();
