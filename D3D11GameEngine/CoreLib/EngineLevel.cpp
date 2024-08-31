#include "Pre.h"
#include "EngineLevel.h"
#include "EngineCamera.h"
#include "EngineCollision.h"

EngineLevel::EngineLevel()
{
}

EngineLevel::~EngineLevel()
{
	DeleteAllChild();
}

void* EngineLevel::CreateActor(void* _NewActor)
{
	EngineLevelObject* NewActor = (EngineLevelObject*)_NewActor;
	NewActor->Input = Input;
	NewActor->Window = Window;
	NewActor->Device = Device;
	NewActor->D3DManager = D3DManager;
	NewActor->SetParent(this);
	NewActor->Awake();
	return _NewActor;
}

void EngineLevel::CreateCamera()
{
	EngineCamera* NewCamera = (EngineCamera*)CreateActor(new EngineCamera());
	CameraList.Add(NewCamera);
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
	UINT AllColCount = CollisionList.GetCount();

	UINT OtherColCount = AllColCount - 1;
	EngineCollision* CurCol = nullptr;
	EngineCollision* OtherCol = nullptr;

	CollisionList.GoFirst();
	for (size_t i = 0; i < AllColCount; i++)
	{
		CurCol = (EngineCollision*)CollisionList.Item();
		CollisionList.GoNext();
		for (size_t j = 0; j < OtherColCount; j++)
		{
			OtherCol = (EngineCollision*)CollisionList.Item();
			CurCol->Collision(OtherCol);
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
	UINT CameraCount = CameraList.GetCount();
	for (UINT i = 0; i < CameraCount; i++)
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

