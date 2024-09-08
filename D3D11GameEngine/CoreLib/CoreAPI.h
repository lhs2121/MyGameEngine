#pragma once
#include <Windows.h>
struct IGameStarter;
struct float4;
struct ICore
{
	virtual void EngineStart(const char* _windowTitle, float4 _windowPos, float4 _windowSize, HINSTANCE _hInstance, IGameStarter* _pStarter) = 0;

	virtual void EngineUpdate() = 0;

	virtual void EngineRelease() = 0;
};
