#pragma once
#include "EngineObject.h"

class EngineActor : public EngineObject
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

	void GetLevel();
	template<typename ComponentType>
	void CreateComponent()
	{
		EngineComponent* NewComponent = new ComponentType();
		NewComponent->Start();
		NewComponent->SetParent(this);
		return;
	}

private:

};

