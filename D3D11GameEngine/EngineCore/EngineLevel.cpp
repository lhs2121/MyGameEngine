#include "Pre.h"
#include "EngineLevel.h"
#include "EngineCamera.h"

EngineLevel::EngineLevel()
{
	EngineCamera* NewCamera = CreateActor<EngineCamera>();
	CameraList.push_back(NewCamera);
}

EngineLevel::~EngineLevel()
{
}

void EngineLevel::Start()
{
}

void EngineLevel::ActorUpdate(float _Delta)
{
	for (EngineObject* Object : ChildList)
	{
		Object->Update(_Delta);
	}
}

void EngineLevel::Update(float _Delta)
{
}

void EngineLevel::Render()
{
	for (EngineCamera* Camera : CameraList)
	{
		Camera->Render();
	}
}

