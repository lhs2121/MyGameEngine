#include "Pre.h"
#include "EngineMemoryPool.h"

EngineMemoryPool::EngineMemoryPool()
{
}

EngineMemoryPool::~EngineMemoryPool()
{
}

bool EngineMemoryPool::IsUsing()
{
	if (HeaderPtr != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
	
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

void* EngineMemoryPool::GetBlock()
{
	void* ReturnBlock = nullptr;

	if (false == DeletedBlocks.empty())
	{
		ReturnBlock = DeletedBlocks.front();
		DeletedBlocks.pop();
	}
	else
	{
		ReturnBlock = NextPtr;
		__int64 CastPtr = (__int64)NextPtr;
		CastPtr += ObjectSize;
		NextPtr = (void*)CastPtr;
	}

	return ReturnBlock;
}

void EngineMemoryPool::DeleteObject(void* Ptr)
{
	memset(Ptr, 0, ObjectSize);

	DeletedBlocks.push(Ptr);
}