#include "Pre.h"
#include "EngineDynamicPool.h"
#include <math.h>

EngineDynamicPool::EngineDynamicPool()
{
}

EngineDynamicPool::~EngineDynamicPool()
{
}

void EngineDynamicPool::Init(int PoolSize)
{
	HeaderPtr = malloc(PoolSize);
	InitPtr = HeaderPtr;
}

void EngineDynamicPool::CleanUp()
{
	free(InitPtr);
}

void* EngineDynamicPool::GetBlock(int _Size)
{
	void* ReturnPtr = HeaderPtr;

	int* intCastPtr =(int*)HeaderPtr;
	*intCastPtr = _Size;
	intCastPtr++;
	HeaderPtr = intCastPtr;

	ReturnPtr = HeaderPtr;

	char* CastPtr = (char*)HeaderPtr;
	CastPtr += _Size;
	HeaderPtr = CastPtr;

	return ReturnPtr;
}

void EngineDynamicPool::FreeBlock(void* Ptr)
{
	int* intCastPtr = (int*)Ptr;
	intCastPtr--;
	Ptr = intCastPtr;

	int BlockSize = *intCastPtr;

	memset(Ptr, 0, BlockSize + sizeof(int));
	FreeBlocks.push(Ptr);
}

int EngineDynamicPool::SizeSearch(int Size)
{
	int BlockSize = 0;
	int i = 4;
	while (true)
	{
		int BlockSize = static_cast<int>(powf(2, (float)i));
		i++;


		if (BlockSize <= Size)
		{
			return BlockSize;
		}

	}
}


