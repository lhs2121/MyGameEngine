#include "Pre.h"
#include "Scene.h"
#include "Camera.h"
#include "Colider.h"

Scene::Scene()
{
}

Scene::~Scene()
{

}

void Scene::CreateCamera()
{
	Camera* newCamera = CreateChild<Camera>();
	cameraList.push_back(newCamera);
}

void Scene::AddCollision(Colider* pCol)
{
	dynamicColiders.push_back(pCol);
	if (pQuadRoot)
	{
		pQuadRoot->Insert(pCol);
	}
}

void Scene::UpdateQuadTree()
{
	pQuadRoot->Clear();
	for (Colider* pCol : dynamicColiders)
	{
		pQuadRoot->Insert(pCol);
	}
	pQuadRoot->CollisionList();
}

void Scene::CheckDeath()
{
	for (Object* object: deathNote)
	{
		object->GetParent()->RemoveChild(object);
		object->AllRelease();
		delete object;
	}
	deathNote.clear();
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

