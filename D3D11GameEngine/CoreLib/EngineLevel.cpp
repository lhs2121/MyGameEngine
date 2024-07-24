#include "Pre.h"
#include "EngineLevel.h"
#include "EngineCamera.h"

EngineLevel::EngineLevel()
{
	EngineCamera* NewCamera = (EngineCamera*)CreateActor(new EngineCamera());

	CameraList.Add(NewCamera);
}

void* EngineLevel::CreateActor(void* _NewActor)
{
	((EngineObject*)_NewActor)->SetParent(this);
	((EngineObject*)_NewActor)->Awake();
	return _NewActor;
}

void EngineLevel::Start()
{
}

void EngineLevel::Update(float _Delta)
{
}

void EngineLevel::Render()
{
	CameraList.GoFirst();

	for (size_t i = 0; i < CameraList.GetCount(); i++)
	{
		EngineCamera* CurCamera = (EngineCamera*)CameraList.Item();
		CurCamera->Render();

		CameraList.GoNext();
	}
}


EngineCamera* EngineLevel::GetMainCamera()
{
	return (EngineCamera*)CameraList.Item();
}
