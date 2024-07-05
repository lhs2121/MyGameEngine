#include "EngineMemoryPool.h"

EngineMemoryPool::EngineMemoryPool()
{
}

EngineMemoryPool::~EngineMemoryPool()
{
}

void EngineMemoryPool::Init(int PoolSize)
{
	HeaderPtr = malloc(PoolSize);
	InitPtr = HeaderPtr;
}

void EngineMemoryPool::CleanUp()
{
	free(InitPtr);
}

void* EngineMemoryPool::GetBlock(int _Size)
{
	void* ReturnPtr = HeaderPtr;

	*(int*)HeaderPtr = _Size;
	int* intCastPtr = (int*)HeaderPtr;
	intCastPtr++;
	HeaderPtr = intCastPtr;

	ReturnPtr = HeaderPtr;

	char* CastPtr = (char*)HeaderPtr;
	CastPtr += _Size;
	HeaderPtr = CastPtr;

	return ReturnPtr;
}

void EngineMemoryPool::FreeBlock(void* Ptr)
{
	int* intCastPtr = (int*)Ptr;
	intCastPtr--;
	Ptr = intCastPtr;

	int BlockSize = *intCastPtr;

	memset(Ptr, 0, BlockSize + sizeof(int));
	FreeBlocks.push(Ptr);
}

int EngineMemoryPool::SizeSearch(int Size)
{
	int BlockSize;
	int i = 4;
	while (true)
	{
		int BlockSize = 2 ^ i;
		i++;


		if (BlockSize > Size)
		{
			return BlockSize;
		}

	}
}


