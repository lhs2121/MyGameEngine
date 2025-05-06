#pragma once
#include <Windows.h>

#ifdef ENGINELIBRARY_EXPORTS
#define ENGINELIBRARY_API __declspec(dllexport)
#else
#define ENGINELIBRARY_API __declspec(dllimport)
#endif 

struct IEngine
{
	virtual void EngineStart(const char* szTitle, float x, float y, float width, float height, HINSTANCE hInstance) = 0;
	virtual void EngineUpdate() = 0;
	virtual void EngineRelease() = 0;
};

extern "C" ENGINELIBRARY_API void CreateEngine(IEngine** ppEngine);
extern "C" ENGINELIBRARY_API void DeleteEngine(IEngine* pEngine);
	
