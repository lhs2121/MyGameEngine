#pragma once
#include "EngineObject.h"

// 설명 :
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
		EngineObject* NewActor = new ActorType();
		NewActor->SetParent(this); //parent를 하고 start를 걸어야함
		NewActor->Start();
		return dynamic_cast<ActorType*>(NewActor);
	}
protected:
	
}; 

