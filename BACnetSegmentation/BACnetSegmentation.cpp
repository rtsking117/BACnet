#include "BACnetSegmentation.h"
#include "SegmentAssembler.h"

CObjectPtr<IBACnetTransactionManager> CreateTransactionManager(U16 MaxSegments)
{
	CSegmentAssembler* temp = new CSegmentAssembler(MaxSegments);
	return CObjectPtr<IBACnetTransactionManager>(temp, true);
}
