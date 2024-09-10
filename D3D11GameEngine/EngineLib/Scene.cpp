#include "Pre.h"
#include "Scene.h"
#include "Camera.h"
#include "Colider2D.h"

Scene::Scene()
{
	collisionList.reserve(100);
}

Scene::~Scene()
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

void Scene::DeleteGameObject(GameObject* _gameObject)
{
	int order = _gameObject->objectOrder;
	allGameObject[order].remove(_gameObject);
}

void Scene::CreateCamera()
{
	Camera* newCamera = CreateGameObject<Camera>();
	cameraList.push_back(newCamera);
}

void Scene::AddCollision(Colider2D* _col)
{
	collisionList.push_back(_col);
}

void Scene::Start()
{
}

void Scene::AllGameObjectStart()
{
	for (auto& pair : allGameObject)
	{
		std::list<GameObject*> curGameObjectList = pair.second;
		for (GameObject* curGameObject : curGameObjectList)
		{
			curGameObject->transform.TransformUpdate();
			curGameObject->AllStart();
		}
	}
}

void Scene::AllGameObjectUpdate(float _deltaTime)
{
	for (auto& pair : allGameObject)
	{
		std::list<GameObject*> curGameObjectList = pair.second;
		for (GameObject* curGameObject : curGameObjectList)
		{
			curGameObject->AllUpdate(_deltaTime);
		}
	}
}

void Scene::AllCollisionUpdate(float _deltaTime)
{
	size_t colCount = collisionList.size();

	Colider2D* firstCol = nullptr;

	for (size_t i = 0; i < colCount; i++)
	{
		firstCol = collisionList[i];

		std::vector<Colider2D*> otherColGroup;
		for (size_t j = i + 1; j < colCount; j++)
		{
			Colider2D* otherCol = collisionList[j];
			otherColGroup.push_back(otherCol);
		}

		for (Colider2D* otherCol : otherColGroup)
		{
			firstCol->Collision(otherCol);
		}
	}
	
}

void Scene::Update(float _deltaTime)
{
}

void Scene::Render()
{
	for (Camera* camera : cameraList)
	{
		camera->Render();
	}
}

Camera* Scene::GetMainCamera()
{
	return cameraList.front();
}

