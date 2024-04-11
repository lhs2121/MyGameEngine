#pragma once
#include "EngineObject.h"
#include "EngineLevel.h"

// Ό³Έν :
class EngineLevelObject : public EngineObject
{
public:
	// constrcuter destructer
	EngineLevelObject();
	~EngineLevelObject();

	// delete Function
	EngineLevelObject(const EngineLevelObject& _Other) = delete;
	EngineLevelObject(EngineLevelObject&& _Other) noexcept = delete;
	EngineLevelObject& operator=(const EngineLevelObject& _Other) = delete;
	EngineLevelObject& operator=(EngineLevelObject&& _Other) noexcept = delete;

	EngineLevel* GetLevel()
	{
		return dynamic_cast<EngineLevel*>(GetTopParent());
	}

};