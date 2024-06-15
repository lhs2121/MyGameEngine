#pragma once
#pragma warning(disable:4099)
#include "DLLCommon.h"
#include "EngineString.h"
#include "EngineMath.h"
#include "EngineTime.h"
#include "EngineDebug.h"
#include "EngineDirectory.h"
#include "EngineFile.h"

struct IEngineMemoryPool
{ 	      
	virtual void  Init(int PoolSize, int _ObjectSize) = 0;
	virtual void  CleanUp() = 0;	    	      
	virtual void* GetBlock() = 0;
	virtual void  FreeBlock(void* Ptr) = 0;
};

extern "C" EngineAPI void CreateMemoryPool(IEngineMemoryPool** ppMemoryPool);