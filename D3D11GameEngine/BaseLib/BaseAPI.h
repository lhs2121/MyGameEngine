#pragma once
#pragma warning(disable:4099)

#include <common/declspec.h>
#include "EngineString.h"
#include "EngineMath.h"
#include "EngineDebug.h"
#include "EngineDirectory.h"
#include "EngineFile.h"
#include "EngineList.h"
#include "EngineHashMap.h"
#include "EngineMap.h"

struct IEngineStaticPool
{ 	    
	virtual void  Init(int _BlockCount, int _BlockSize) = 0;
	virtual void  CleanUp() = 0;	    	      
	virtual void* GetBlock() = 0;
	virtual void  FreeBlock(void* Ptr) = 0;
};

struct IEngineTime
{
	virtual void  Init() = 0;
	virtual void  CountStart() = 0;
	virtual float CountEnd() = 0;
};

extern "C" BaseAPI void CreateEngineStaticPool(IEngineStaticPool** ppI);
extern "C" BaseAPI void DeleteEngineStaticPool(IEngineStaticPool* pI);

extern "C" BaseAPI void CreateEngineTime(IEngineTime** ppI);
extern "C" BaseAPI void DeleteEngineTime(IEngineTime* pI);