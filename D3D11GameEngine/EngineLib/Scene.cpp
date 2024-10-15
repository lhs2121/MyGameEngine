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

