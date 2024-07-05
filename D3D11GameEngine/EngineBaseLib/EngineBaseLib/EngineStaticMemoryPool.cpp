#include "Pre.h"
#include "EngineStaticMemoryPool.h"

EngineStaticMemoryPool::EngineStaticMemoryPool()
{
}

EngineStaticMemoryPool::~EngineStaticMemoryPool()
{
	CleanUp();
}


void EngineStaticMemoryPool::Init(int PoolSize, int _ObjectSize)
{
	HeaderPtr = malloc(PoolSize);
	memset(HeaderPtr, 0, PoolSize);
	NextPtr = HeaderPtr;
	ObjectSize = _ObjectSize;
}

void EngineStaticMemoryPool::CleanUp()
{
	if (HeaderPtr != nullptr)
	{
		free(HeaderPtr);
		HeaderPtr = nullptr;
	}
}

void* EngineStaticMemoryPool::GetBlock()
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

void EngineStaticMemoryPool::FreeBlock(void* Ptr)
{
	FreeBlocks.push(Ptr);
}