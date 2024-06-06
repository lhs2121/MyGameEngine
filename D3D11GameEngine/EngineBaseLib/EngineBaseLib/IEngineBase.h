#pragma once
#pragma warning(disable:4099)

#include "EngineMath.h"
#include "EngineString.h"
struct IEngineMemoryPool
{ 	      
	virtual void  Init(int PoolSize, int _ObjectSize) = 0;
	virtual void  CleanUp() = 0;	    	      
	virtual void* GetBlock() = 0;
	virtual void  FreeBlock(void* Ptr) = 0;
};

extern "C" __declspec(dllexport) void CreateMemoryPool(IEngineMemoryPool ** ppMemoryPool);