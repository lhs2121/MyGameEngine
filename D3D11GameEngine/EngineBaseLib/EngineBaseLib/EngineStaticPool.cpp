#include "Pre.h"
#include "EngineStaticPool.h"

EngineStaticPool::EngineStaticPool()
{
}

EngineStaticPool::~EngineStaticPool()
{
	CleanUp();
}


void EngineStaticPool::Init(int PoolSize, int _ObjectSize)
{
	HeaderPtr = malloc(PoolSize);
	memset(HeaderPtr, 0, PoolSize);
	NextPtr = HeaderPtr;
	ObjectSize = _ObjectSize;
}

void EngineStaticPool::CleanUp()
{
	if (HeaderPtr != nullptr)
	{
		free(HeaderPtr);
		HeaderPtr = nullptr;
	}
}

void* EngineStaticPool::GetBlock()
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

void EngineStaticPool::FreeBlock(void* Ptr)
{
	try 
	{
		FreeBlocks.push(Ptr);
	}
	catch (const std::exception& e) 
	{
		const char* a = e.what();
	}
}
