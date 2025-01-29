#pragma once

#include <unordered_map>

class TransactionSet;

#include "Transaction.h"

class TransactionSet : 
	public ObjectWrapper<IBACnetUnknown>
{
	typedef std::pair<U8, CObjectPtr<IBACnetNetworkAddress>> TransactionKey;
	struct HashAddressPair
	{
		size_t operator()(const TransactionKey& _Keyval) const;
	};
	typedef std::unordered_map<TransactionKey, CObjectPtr<CTransaction>, HashAddressPair> TransactionMap;
	TransactionMap m;
	SRWLOCK lock;

public:
	TransactionSet();
	~TransactionSet();

	CObjectPtr<CTransaction> Find(U8 InvokeID, CObjectPtr<IBACnetNetworkAddress> pAddr);
	bool Add(CObjectPtr<CTransaction> trx);
	bool Remove(CObjectPtr<CTransaction> trx);
};

