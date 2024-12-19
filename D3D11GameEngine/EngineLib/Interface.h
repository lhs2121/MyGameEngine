#pragma once
#include <Windows.h>

struct Engine;
struct Initializer
{
	virtual void CreateAllScene(Engine* pMainEngine) = 0;
};

struct IEngine
{
	virtual void EngineStart(const char* szTitle, float x, float y, float width, float height, HINSTANCE hInstance, Initializer* pGameInit) = 0;
	virtual void EngineUpdate() = 0;
	virtual void EngineRelease() = 0;
};
	
