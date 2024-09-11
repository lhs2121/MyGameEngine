#pragma once
#include <Windows.h>
struct SceneManager;
struct IEngine
{
	virtual void EngineStart(const char* _windowTitle, float _windowPosX, float _windowPosY, float _windowSizeX, float _windowSizeY, HINSTANCE _hInstance, SceneManager* _pSceneManager) = 0;

	virtual void EngineUpdate() = 0;

	virtual void EngineRelease() = 0;
};
