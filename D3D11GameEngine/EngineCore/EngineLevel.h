#pragma once
#include "EngineObject.h"

// ���� :
class EngineRenderer;
class EngineCamera;
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
	void ActorUpdate(float _Delta);
	void Update(float _Delta) override;
	void Render();
	template<typename ActorType>
	ActorType* CreateActor()
	{
		EngineObject* NewActor = new ActorType();

		//Start()�ȿ��� Level�� �����Ҽ��������� SetParent�� �ɰ� Start�� ȣ������
		NewActor->SetParent(this); 
		NewActor->Start();
		return dynamic_cast<ActorType*>(NewActor);
	}

	EngineCamera* GetMainCamera()
	{
		return (*CameraList.begin());
	}

private:
	std::list<EngineRenderer*> RendererList;
	std::list<EngineCamera*> CameraList;
}; 
