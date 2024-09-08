#include "Pre.h"
#include "Level.h"
#include "Camera.h"
#include "Colider2D.h"

Level::Level()
{
}

Level::~Level()
{
	for (auto& pair: allGameObject)
	{
		GameObject* curGameObject = pair.second;
		delete curGameObject;
	}
	allGameObject.clear();
}

void Level::CreateCamera()
{
	Camera* newCamera = CreateGameObject<Camera>();
	cameraList.push_back(newCamera);
}

void Level::AddCollision(Colider2D* _col)
{
	collisionList.push_back(_col);
}

void Level::Start()
{
}

void Level::AllGameObjectUpdate(float _deltaTime)
{
	for (auto& pair : allGameObject)
	{
		GameObject* curObject = pair.second;
		curObject->ChildUpdate(_deltaTime);
	}
}

void Level::Update(float _deltaTime)
{
}

void Level::Render()
{
	for (Camera* camera : cameraList)
	{
		camera->Render();
	}
}

Camera* Level::GetMainCamera()
{
	return cameraList.front();
}

