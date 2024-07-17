#pragma once
#include "CoreAPI.h"
#include "EngineObject.h"

class EngineCamera;
class EngineActor;
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

	void* CreateActor(const char* _Name, void* _NewActor)
	{
		((EngineObject*)_NewActor)->SetParent(this);
		((EngineObject*)_NewActor)->Awake();
		return _NewActor;
	}

	EngineObject* GetMainCamera()
	{
		return *(CameraList.begin());
	}

private:
	std::list<EngineObject*> CameraList;
};

