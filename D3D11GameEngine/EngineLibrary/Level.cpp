#include "pch.h"
#include "Level.h"

GameObject* Level::CreateGameObject()
{
	GameObject* obj = new GameObject;
	obj->name = "GameObject";
	return obj;
}

void Level::UpdateGameObjects(float deltaTime)
{
	for (GameObject* obj : gameObjectList)
	{
		if (!obj->isUpdate)
			continue;

		if (obj->isTransformChanged)
		{
			obj->TransformUpdate();
			obj->isTransformChanged = false;
		}

		obj->Update(deltaTime);
	}
}

void Level::ReleaseGameObjects()
{
	for (GameObject* obj : gameObjectList)
	{
		if (obj->isDestroy)
		{
			obj->Release();
		}
	}
}
