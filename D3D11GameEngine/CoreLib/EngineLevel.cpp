#include "Pre.h"
#include "EngineLevel.h"
#include "EngineCamera.h"

EngineLevel::EngineLevel()
{
	EngineCamera* NewCamera = (EngineCamera*)CreateActor(new EngineCamera());

	CameraList.push_back(NewCamera);
}

EngineLevel::~EngineLevel()
{
}

void EngineLevel::Start()
{
}

void EngineLevel::Update(float _Delta)
{
}

void EngineLevel::Render()
{
	for (EngineObject* Camera : CameraList)
	{
		((EngineCamera*)Camera)->Render();
	}
}

