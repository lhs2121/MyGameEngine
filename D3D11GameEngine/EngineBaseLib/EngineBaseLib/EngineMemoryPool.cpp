#include "Pre.h"
#include "EngineMemoryPool.h"

EngineMemoryPool::EngineMemoryPool()
{
}

EngineMemoryPool::~EngineMemoryPool()
{
	CleanUp();
}


void EngineMemoryPool::Init(int PoolSize, int _ObjectSize)
{
	HeaderPtr = malloc(PoolSize);
	memset(HeaderPtr, 0, PoolSize);
	NextPtr = HeaderPtr;
	ObjectSize = _ObjectSize;
}

void EngineMemoryPool::CleanUp()
{
	if (HeaderPtr != nullptr)
	{
		free(HeaderPtr);
		HeaderPtr = nullptr;
	}
}

void* EngineMemoryPool::GetBlock()
{
	void* ReturnBlock = nullptr;

	if (false == FreeBlocks.empty())
	{
		ReturnBlock = FreeBlocks.front();
		FreeBlocks.pop();
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

void EngineMemoryPool::FreeBlock(void* Ptr)
{
	FreeBlocks.push(Ptr);
}