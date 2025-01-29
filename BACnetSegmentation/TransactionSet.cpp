#include "TransactionSet.h"
#include <cstddef>

TransactionSet::TransactionSet()
{
	InitializeSRWLock(&lock);
}

TransactionSet::~TransactionSet()
{
	m.clear();
}

CObjectPtr<CTransaction> TransactionSet::Find(U8 InvokeID, CObjectPtr<IBACnetNetworkAddress> pAddr)
{
	AcquireSRWLockShared(&lock);
	auto v = m.find(TransactionKey(InvokeID, pAddr));
	if(v == m.end())
	{
		ReleaseSRWLockShared(&lock);
		return nullptr;
	}
	ReleaseSRWLockShared(&lock);
	return v->second;
}

bool TransactionSet::Add(CObjectPtr<CTransaction> trx)
{
	AcquireSRWLockExclusive(&lock);
	auto it = m.insert(std::pair<TransactionKey, CObjectPtr<CTransaction>>(TransactionKey(trx->GetInvokeID(), trx->GetSender()), trx));
	ReleaseSRWLockExclusive(&lock);
	return it.second;
}

bool TransactionSet::Remove(CObjectPtr<CTransaction> trx)
{
	AcquireSRWLockExclusive(&lock);
	size_t v = m.erase(TransactionKey(trx->GetInvokeID(), trx->GetSender()));
	ReleaseSRWLockExclusive(&lock);
	return v == 1;
}

size_t TransactionSet::HashAddressPair::operator()(const TransactionKey& Key) const
{
	U16 net = Key.second->GetNetworkID();
	CObjectPtr<IBACnetAddress> portaddr = Key.second->GetPortAddress();
	U32 len = 0;
	if(portaddr)
	{
		len = portaddr->GetAddressLength();
	}
	U8* buffer = (U8*)alloca(3 + len);
	buffer[0] = Key.first;
	buffer[1] = ((net >> 8) & 0xFF);
	buffer[2] = (net & 0xFF);
	if(portaddr)
	{
		portaddr->WriteAddress(&buffer[3], len);
	}
	return GenerateHash(buffer, 3 + len);
}
