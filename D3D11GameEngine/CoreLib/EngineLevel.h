#pragma once
#include "CoreLibAPI.h"
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
	void Update(float _Delta) override;
	void Render();

	IObject* CreateActor(IObject* _NewActor) override
	{
		_NewActor->SetParent(this);
		_NewActor->Start();
		return _NewActor;
	}

	IObject* GetMainCamera() override
	{
		return (IObject*)(*CameraList.begin());
	}

private:
	std::list<EngineObject*> CameraList;
};

