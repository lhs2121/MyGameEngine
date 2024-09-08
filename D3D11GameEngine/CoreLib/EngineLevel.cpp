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

void EngineLevel::CreateCamera()
{
	EngineCamera* NewCamera = (EngineCamera*)CreateObject(new EngineCamera());
	CameraList.push_back(NewCamera);
}

void EngineLevel::AddCollision(EngineCollision* _Col)
{
	CollisionList.push_back(_Col);
}

void EngineLevel::Start()
{
}

void EngineLevel::Update(float _Delta)
{
	EngineCollision* CurCol = nullptr;
	EngineCollision* OtherCol = nullptr;

	for (auto col : CollisionList)
	{
		CurCol = col;

		for (auto col2 : CollisionList)
		{

		}
	}
}

void EngineLevel::Render()
{
	for (auto ele : CameraList)
	{
		ele->Render();
	}
}

EngineCamera* EngineLevel::GetMainCamera()
{
	return CameraList.front();
}

