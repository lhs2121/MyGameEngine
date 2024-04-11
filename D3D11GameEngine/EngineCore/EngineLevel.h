#pragma once
#include "EngineActor.h"

// Ό³Έν :
class EngineLevel : public EngineObject
{
public:
	// constrcuter destructer
	EngineLevel();
	~EngineLevel();

	// delete Function
	EngineLevel(const EngineLevel& _Other) = delete;
	EngineLevel(EngineLevel&& _Other) noexcept = delete;
	EngineLevel& operator=(const EngineLevel& _Other) = delete;
	EngineLevel& operator=(EngineLevel&& _Other) noexcept = delete;

	void Start() override;
	void Update(float _Delta) override;

	template<typename ActorType>
	ActorType* CreateActor()
	{
		EngineActor* NewActor = new ActorType();
		NewActor->Start();
		NewActor->SetParent(this);
		return dynamic_cast<ActorType*>(NewActor);
	}
protected:
	
}; 

