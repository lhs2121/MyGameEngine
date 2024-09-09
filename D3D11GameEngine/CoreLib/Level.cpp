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
		std::list<GameObject*> curGameObjectList = pair.second;
		for (GameObject* curGameObject : curGameObjectList)
		{
			delete curGameObject;
		}
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
		std::list<GameObject*> curGameObjectList = pair.second;
		for (GameObject* curGameObject : curGameObjectList)
		{
			curGameObject->ChildUpdate(_deltaTime);
		}
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

