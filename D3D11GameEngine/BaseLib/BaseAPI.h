#pragma once
#pragma warning(disable:4099)

#include <common/declspec.h>
#include <Windows.h>
#include "EngineMath.h"
#include "EngineList.h"
#include "basestring.h"

namespace Debug
{
	extern "C" BaseAPI void CrtSetBreakAlloc(UINT num);
	extern "C" BaseAPI void CrtSetDbgFlag();
	extern "C" BaseAPI void MsgBoxAssert(const char* errorMsg);
}

struct IEngineStaticPool
{ 	    
	virtual void  Init(int _BlockCount, int _BlockSize) = 0;
	virtual void  CleanUp() = 0;	    	      
	virtual void* GetBlock() = 0;
	virtual void  FreeBlock(void* Ptr) = 0;
};

struct ITime
{
	virtual void  Init() = 0;
	virtual void  CountStart() = 0;
	virtual float CountEnd() = 0;
};

extern "C" BaseAPI void CreateEngineStaticPool(IEngineStaticPool** ppI);
extern "C" BaseAPI void DeleteEngineStaticPool(IEngineStaticPool* pI);

extern "C" BaseAPI void CreateEngineTime(ITime** ppI);
extern "C" BaseAPI void DeleteEngineTime(ITime* pI);