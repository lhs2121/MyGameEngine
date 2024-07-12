#pragma once
#include "EngineObject.h"

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

	EngineObject* CreateActor(int _ActorSize, EngineObject* _NewActor)
	{
		_NewActor->SetParent(this);
		_NewActor->Start();
		return _NewActor;
	}

	EngineCamera* GetMainCamera()
	{
		return (EngineCamera*)(*CameraList.begin());
	}

private:
	std::list<EngineObject*> RendererList;
	std::list<EngineObject*> CameraList;
};

