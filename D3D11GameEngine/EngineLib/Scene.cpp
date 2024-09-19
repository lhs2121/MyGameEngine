#include "Pre.h"
#include "Scene.h"
#include "Camera.h"
#include "Colider.h"

Scene::Scene()
{
	collisionList.reserve(100);
}

void Scene::CreateCamera()
{
	Camera* newCamera = CreateChild<Camera>();
	cameraList.push_back(newCamera);
}

void Scene::AddCollision(Colider* _col)
{
	collisionList.push_back(_col);
}

void Scene::Collision(float _deltaTime)
{
	size_t colCount = collisionList.size();

	Colider* firstCol = nullptr;

	for (size_t i = 0; i < colCount; i++)
	{
		firstCol = collisionList[i];

		std::vector<Colider*> otherColGroup;
		for (size_t j = i + 1; j < colCount; j++)
		{
			Colider* otherCol = collisionList[j];
			otherColGroup.push_back(otherCol);
		}

		for (Colider* otherCol : otherColGroup)
		{
			firstCol->Collision(otherCol);
		}
	}
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

