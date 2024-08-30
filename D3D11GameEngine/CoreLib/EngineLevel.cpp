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

	UINT OtherColCount = Count - 1;
	EngineCollision* CurCol = nullptr;
	EngineCollision* OtherCol = nullptr;

	for (size_t i = 0; i < Count; i++)
	{
		CurCol = (EngineCollision*)CollisionList.Item();
		CollisionList.GoNext();
		for (size_t j = 0; j < OtherColCount; j++)
		{
			OtherCol = (EngineCollision*)CollisionList.Item();
			CurCol->AABB(OtherCol);
			CollisionList.GoNext();
		}

		OtherColCount--;
		if (OtherColCount == 0)
		{
			break;
		}


		CollisionList.GoFirst();
		for (size_t k = 0; k < i + 1; k++)
		{
			CollisionList.GoNext();
		}
		
	}

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
