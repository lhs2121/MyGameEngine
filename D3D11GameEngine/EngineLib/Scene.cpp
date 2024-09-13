#include "Pre.h"
#include "Scene.h"
#include "Camera.h"
#include "Colider2D.h"

Scene::Scene()
{
	collisionList.reserve(100);
}

void Scene::CreateCamera()
{
	Camera* newCamera = CreateChild<Camera>();
	cameraList.push_back(newCamera);
}

void Scene::AddCollision(Colider2D* _col)
{
	collisionList.push_back(_col);
}

void Scene::Collision(float _deltaTime)
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

