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
	for(Renderer* r: collisionDebugRenderers)
	{
		delete r;
	}

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
	const char* meshName = nullptr;
	switch (_col->colType)
	{
	case ColType::AABB2D :
		meshName = "Box2D";
		break;
	case ColType::Circle2D :
		meshName = "Circle2D";
		break;
	default:
		break;
	}
	collisionList.push_back(_col);
	Renderer* debugRenderer = new Renderer();

	debugRenderer->transform.SetParent(&_col->transform);
	debugRenderer->scene = this;

	debugRenderer->Awake();
	debugRenderer->SetRenderOrder(-5);
	debugRenderer->SetMesh(meshName);
	debugRenderer->SetMaterial("WireFrame");

	collisionDebugRenderers.push_back(debugRenderer);
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

