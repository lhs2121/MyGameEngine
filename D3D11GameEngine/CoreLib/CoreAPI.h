#pragma once
#include <common/declspec.h>
#include <Windows.h>
class  EngineString;
class  EngineObject;
struct IGameStarter;
struct float4;

struct ICore
{
	virtual void EngineStart(const char* _WindowTitle, float4 _WindowPos, float4 _WindowSize, HINSTANCE _hInstance, IGameStarter* _Starter) = 0;

	virtual void EngineUpdate() = 0;

	virtual void EngineRelease() = 0;
};
