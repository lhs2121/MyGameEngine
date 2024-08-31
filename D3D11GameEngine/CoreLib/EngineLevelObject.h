#pragma once
#include "EngineObject.h"

// ���� :
class EngineLevel;
class CoreAPI EngineLevelObject : public EngineObject
{
public:
	EngineLevel* GetLevel();

	IEngineInput* Input = nullptr;
	IEngineWindow* Window = nullptr;
	IEngineDevice* Device = nullptr;
	IEngineD3DManager* D3DManager = nullptr;
};