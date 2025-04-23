#include "pch.h"
#include "Level.h"

void Level::AllUpdate(float deltaTime)
{
	for (GameObject* obj: gameObjectList)
	{
		obj->TransformUpdate();
		obj->Update(deltaTime);
	}
}
