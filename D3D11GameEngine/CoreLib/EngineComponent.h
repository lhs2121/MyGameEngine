#pragma once
#include "EngineLevelObject.h"

// Ό³Έν :
class EngineComponent : public EngineLevelObject
{
public:
	// constrcuter destructer
	EngineComponent();
	~EngineComponent();

	// delete Function
	EngineComponent(const EngineComponent& _Other) = delete;
	EngineComponent(EngineComponent&& _Other) noexcept = delete;
	EngineComponent& operator=(const EngineComponent& _Other) = delete;
	EngineComponent& operator=(EngineComponent&& _Other) noexcept = delete;

private:

};