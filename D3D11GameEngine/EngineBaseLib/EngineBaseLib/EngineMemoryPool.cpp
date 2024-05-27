#include "Pre.h"
#include "EngineMemoryPool.h"

EngineMemoryPool::EngineMemoryPool()
{
}

EngineMemoryPool::~EngineMemoryPool()
{
}

void EngineMemoryPool::CreatePool(int PoolSize, int _ObjectSize)
{
	HeaderPtr = malloc(PoolSize);
	memset(HeaderPtr, 0, PoolSize);
	NextPtr = HeaderPtr;
	ObjectSize = _ObjectSize;
}

void EngineMemoryPool::DeletePool()
{
	free(HeaderPtr);
}

void* EngineMemoryPool::InsertObject(void* Ptr)
{
	memcpy_s(NextPtr, ObjectSize, Ptr, ObjectSize);
	void* ReturnPtr = NextPtr;

	// NextPtr¿Å±è
	__int64 CastPtr = (__int64)NextPtr;
	CastPtr += ObjectSize;
	NextPtr = (void*)CastPtr;

	return ReturnPtr;
}
void EngineMemoryPool::DeleteObject(void* Ptr)
{
	memset(Ptr, 0, ObjectSize);
}