#include "Pre.h"
#include "EngineStaticPool.h"

EngineStaticPool::EngineStaticPool()
{
}

EngineStaticPool::~EngineStaticPool()
{
	CleanUp();
}


void EngineStaticPool::Init(int _BlockCount, int _BlockSize)
{
	int PoolSize = _BlockCount * _BlockSize;

	InitPtr = malloc(PoolSize);

	if (InitPtr != nullptr)
	{
		memset(InitPtr, 0, PoolSize);
	}
	HeaderPtr = InitPtr;
	BlockSize = _BlockSize;
}

void EngineStaticPool::CleanUp()
{
	if (InitPtr != nullptr)
	{
		free(InitPtr);
		InitPtr = nullptr;
	}
}

void* EngineStaticPool::GetBlock()
{
	void* Result = nullptr;

	if (FreeBlocks.empty() == true)
	{
		Result = HeaderPtr;
		HeaderPtr = (char*)HeaderPtr + BlockSize;
	}
	else
	{
		Result = FreeBlocks.back();
		FreeBlocks.pop_back();
	}

	return Result;
}

void EngineStaticPool::FreeBlock(void* Ptr)
{
	FreeBlocks.push_back(Ptr);
}