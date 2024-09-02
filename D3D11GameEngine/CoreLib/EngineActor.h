#pragma once
#include "EngineLevelObject.h"
#include "EngineComponent.h"

class CoreAPI EngineActor : public EngineLevelObject
{
public:
	EngineObject* CreateComponent(EngineObject* _NewActor)
	{
		EngineLevelObject* NewActor = (EngineLevelObject*)_NewActor;
		NewActor->Input = Input;
		NewActor->Window = Window;
		NewActor->Device = Device;
		NewActor->D3DManager = D3DManager;
		_NewActor->SetParent(this);
		_NewActor->Awake();
		return _NewActor;
	}

	EngineComponent* GetComponent(const char* _Name);
};

