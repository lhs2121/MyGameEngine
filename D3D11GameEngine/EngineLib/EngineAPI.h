#pragma once
#include <Windows.h>
struct Initializer;
struct IEngine
{
	virtual void EngineStart(const char* _windowTitle, float _windowPosX, float _windowPosY, float _windowSizeX, float _windowSizeY, HINSTANCE _hInstance, Initializer* pGameInit) = 0;

	virtual void EngineUpdate() = 0;

	virtual void EngineRelease() = 0;
};
			