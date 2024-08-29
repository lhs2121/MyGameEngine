#include "Pre.h"
#include "EngineLevel.h"
#include "EngineCamera.h"
#include "EngineCollision.h"

EngineLevel::EngineLevel()
{
	EngineCamera* NewCamera = (EngineCamera*)CreateActor(new EngineCamera());

	CameraList.Add(NewCamera);
}

EngineLevel::~EngineLevel()
{
	DeleteAllChild();
}

void* EngineLevel::CreateActor(void* _NewActor)
{
	((EngineObject*)_NewActor)->SetParent(this);
	((EngineObject*)_NewActor)->Awake();
	return _NewActor;
}

void EngineLevel::AddCollision(EngineCollision* _Col)
{
	CollisionList.Add(_Col);
}

void EngineLevel::Start()
{
}

void EngineLevel::Update(float _Delta)
{
	UINT Count = CollisionList.GetCount();
	EngineCollision* Col1 = nullptr;
	EngineCollision* Col2 = nullptr;
	for (size_t i = 0; i < Count; i++)
	{
		if (i == 0)
		{
			Col1 = (EngineCollision*)CollisionList.Item();
		}
		if (i == 1)
		{
			Col2 = (EngineCollision*)CollisionList.Item();
		}
		CollisionList.GoNext();
	}
	Col1->AABB(Col2);
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
