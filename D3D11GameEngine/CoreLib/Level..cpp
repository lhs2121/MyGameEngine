#include "Pre.h"
#include "Level.h"
#include "Camera.h"
#include "Colider2D.h"

Level::Level()
{
}

Level::~Level()
{
	DeleteAllChild();
}

void Level::CreateCamera()
{
	Camera* NewCamera = (Camera*)CreateObject(new Camera());
	CameraList.push_back(NewCamera);
}

void Level::AddCollision(Colider2D* _Col)
{
	CollisionList.push_back(_Col);
}

void Level::Start()
{
}

void Level::Update(float _Delta)
{
	Colider2D* CurCol = nullptr;
	Colider2D* OtherCol = nullptr;

	for (auto col : CollisionList)
	{
		CurCol = col;

		for (auto col2 : CollisionList)
		{

		}
	}
}

void Level::Render()
{
	for (auto ele : CameraList)
	{
		ele->Render();
	}
}

Camera* Level::GetMainCamera()
{
	return CameraList.front();
}

