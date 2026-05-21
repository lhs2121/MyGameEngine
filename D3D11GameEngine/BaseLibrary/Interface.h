#pragma once
#pragma warning(disable:4099)

#ifdef BASELIBRARY_EXPORTS 
#define BASELIBRARY_API __declspec(dllexport)
#else
#define BASELIBRARY_API __declspec(dllimport)
#endif

#include <Windows.h>
#include "EngineMath.h"

namespace Debug
{
	extern "C" BASELIBRARY_API void CrtSetBreakAlloc(UINT num);
	extern "C" BASELIBRARY_API void CrtSetDbgFlag();
	extern "C" BASELIBRARY_API void MsgBoxAssert(const char* errorMsg);
}

struct ITimeObject
{
	virtual void  Initialize() = 0;
	virtual void  CountStart() = 0;
	virtual float CountEnd() = 0;
};

extern "C" BASELIBRARY_API void CreateTimeObject(ITimeObject** ppTimeObject);
extern "C" BASELIBRARY_API void DeleteTimeObject(ITimeObject* pTimeObject);
