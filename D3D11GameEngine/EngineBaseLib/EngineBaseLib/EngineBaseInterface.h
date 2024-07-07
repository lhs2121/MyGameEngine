#pragma once
#pragma warning(disable:4099)

#include "EngineString.h"
#include "EngineMath.h"
#include "EngineTime.h"
#include "EngineDebug.h"
#include "EngineDirectory.h"
#include "EngineFile.h"

struct IEngineStaticPool
{ 	    
	virtual void  Init(int PoolSize, int _ObjectSize) = 0;
	virtual void  CleanUp() = 0;	    	      
	virtual void* GetBlock() = 0;
	virtual void  FreeBlock(void* Ptr) = 0;
};

struct IEngineDynamicPool
{
	virtual void  Init(int PoolSize) = 0;
	virtual void  CleanUp() = 0;
	virtual void* GetBlock(int _Size) = 0;
	virtual void  FreeBlock(void* Ptr) = 0;
};

extern "C" EngineBaseAPI void CreateEngineStaticPool(IEngineStaticPool** ppIEngineStaticPool);
extern "C" EngineBaseAPI void DeleteEngineStaticPool(IEngineStaticPool* pIEngineStaticPool);

extern "C" EngineBaseAPI void CreateEngineDynamicPool(IEngineDynamicPool** ppIEngineDynamicPool);
extern "C" EngineBaseAPI void DeleteEngineDynamicPool(IEngineDynamicPool* pIEngineDynamicPool);
