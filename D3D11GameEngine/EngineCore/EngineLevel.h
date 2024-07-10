#pragma once
#include "EngineObject.h"

// Ό³Έν :
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

	void* CreateActor(int _ActorSize, void* _pDummy)
	{
		void* Result = malloc(_ActorSize);
		memcpy_s(Result, _ActorSize, _pDummy, _ActorSize);
		EngineObject* CastPtr = (EngineObject*)Result;
		CastPtr->SetParent(this);
		CastPtr->Start();

		//delete _pDummy;
		return Result;
	}

	EngineCamera* GetMainCamera()
	{
		return (*CameraList.begin());
	}

private:
	std::list<EngineRenderer*> RendererList;
	std::list<EngineCamera*> CameraList;
};

