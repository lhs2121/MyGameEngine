#include "Pre.h"
#include "Scene.h"
#include "Camera.h"
#include "Colider.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	for (auto& pair: colGroups)
	{
		delete pair.second;
	}
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

void Scene::AddCollision(Colider* _col)
{
	if (colGroups.find(0) == colGroups.end())
	{
		colGroups[0] = new ColGroup();
	}

	colGroups[0]->colList.push_back(_col);
	_col->parentGroup = colGroups[0];
	_col->colOrder = 0;
}

void Scene::RemoveCollision(Colider* _col)
{
	colGroups[0]->colList.remove(_col);
	_col->parentGroup = nullptr;
}

ColGroup* Scene::GetGroup(int _order)
{
	if (colGroups.find(_order) == colGroups.end())
	{
		colGroups[_order] = new ColGroup();
	}

	return colGroups[_order];
}

void Scene::SetColOrder(Colider* _col, int _order)
{
	colGroups[_col->colOrder]->colList.remove(_col);

	if (colGroups.find(_order) == colGroups.end())
	{
		colGroups[_order] = new ColGroup();
	}
	colGroups[_order]->colList.push_back(_col);
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

