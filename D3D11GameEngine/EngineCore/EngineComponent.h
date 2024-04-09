#pragma once
#include "EngineObject.h"

// ���� :
class EngineComponent : public EngineObject
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