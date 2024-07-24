#pragma once
#include "EngineLevelObject.h"
#include "EngineComponent.h"

class CoreAPI EngineActor : public EngineLevelObject
{
public:
	EngineObject* CreateComponent(EngineObject* _NewActor)
	{
		_NewActor->SetParent(this);
		_NewActor->Awake();
		return _NewActor;
	}
};

