#include "pch.h"
#include "EngineStaticPool.h"

EngineStaticPool::~EngineStaticPool()
{
	if (InitPtr != nullptr)
	{
		free(InitPtr);
	}
}

void EngineStaticPool::Init(int _BlockCount, int _BlockSize)
{
	Queue.Init(_BlockCount);

	int PoolSize = _BlockCount * _BlockSize;
	InitPtr = malloc(PoolSize);

	if (InitPtr != nullptr)
	{
		memset(InitPtr, 0, PoolSize);
	}

	HeaderPtr = InitPtr;
	BlockCount = _BlockCount;
	BlockSize = _BlockSize;
}

void EngineStaticPool::CleanUp()
{
	if (InitPtr != nullptr)
	{
		int PoolSize = BlockCount * BlockSize;
		memset(InitPtr, 0, PoolSize);
	}
}

void* EngineStaticPool::GetBlock()
{
	void* Result = nullptr;

	if (Queue.Empty())
	{
		Result = HeaderPtr;
		HeaderPtr = (char*)HeaderPtr + BlockSize;

		return Result;
	}
	
	Result = Queue.Pop();
	return Result;
}

void EngineStaticPool::FreeBlock(void* Ptr)
{
	Queue.Push(Ptr);
}

FreeQueue::~FreeQueue()
{
	if (PtrArray != nullptr)
	{
		delete[] PtrArray;
		PtrArray = nullptr;
	}
}

void FreeQueue::Init(int _PtrCount)
{
	PtrCount = _PtrCount;
	PtrArray = new void* [PtrCount];
	memset(PtrArray, 0, PtrCount * sizeof(void*));
}

bool FreeQueue::Empty()
{
	if (PtrArray[0] == nullptr)
	{
		return true;
	}
	return false;
}

void FreeQueue::Push(void* _Ptr)
{
	for (int i = 0; i < PtrCount; i++)
	{
		if (PtrArray[i] == nullptr)
		{
			PtrArray[i] = _Ptr;
			LastIndex = i;

			return;
		}
	}
}

void* FreeQueue::Pop()
{
	if (Empty())
	{
		return nullptr;
	}
	void* Result = PtrArray[LastIndex]; 
	memset(&PtrArray[LastIndex], 0, sizeof(void*));

	if (LastIndex != 0)
	{
		LastIndex -= 1;
	}


	return Result;
}
