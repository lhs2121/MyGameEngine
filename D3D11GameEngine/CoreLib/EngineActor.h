#pragma once
#include "EngineLevelObject.h"
#include "EngineComponent.h"

class EngineActor : public EngineLevelObject
{
public:
	// constrcuter destructer
	EngineActor();
	~EngineActor();

	// delete Function
	EngineActor(const EngineActor& _Other) = delete;
	EngineActor(EngineActor&& _Other) noexcept = delete;
	EngineActor& operator=(const EngineActor& _Other) = delete;
	EngineActor& operator=(EngineActor&& _Other) noexcept = delete;

	EngineObject* CreateComponent(EngineObject* _NewActor)
	{
		_NewActor->SetParent(this);
		_NewActor->Start();
		return _NewActor;
	}
};

