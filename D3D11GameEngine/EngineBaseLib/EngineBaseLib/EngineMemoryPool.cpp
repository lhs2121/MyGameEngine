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

void* EngineMemoryPool::InsertObject(void* Ptr, int Size)
{
	if (Size == -1)
	{
		Size = ObjectSize;
	}
	memcpy_s(NextPtr, Size, Ptr, Size);
	void* ReturnPtr = NextPtr;

	// NextPtr 오프셋이동

	while (true)
	{
		__int64 CastPtr = (__int64)NextPtr;
		CastPtr += ObjectSize;
		NextPtr = (void*)CastPtr;

		if (*(char*)NextPtr == 0)
		{
			break;
		}
	}


	return ReturnPtr;
}
void EngineMemoryPool::DeleteObject(void* Ptr)
{
	memset(Ptr, 0, ObjectSize);
	NextPtr = Ptr;
}