#pragma once
#include "EngineObject.h"

// ���� :
class EngineRenderer;
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
	void Render();

	void PushRenderer(EngineRenderer* Renderer)
	{
		RendererList.push_back(Renderer);
	}

	template<typename ActorType>
	ActorType* CreateActor()
	{
		EngineObject* NewActor = new ActorType();
		NewActor->SetParent(this); //parent�� �ϰ� start�� �ɾ����
		NewActor->Start();
		return dynamic_cast<ActorType*>(NewActor);
	}

private:
	std::list<EngineRenderer*> RendererList;
	
}; 

