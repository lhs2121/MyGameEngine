#pragma once
#include <list>
#include "GameObject.h"
class Level
{
public:
	void AllUpdate(float deltaTime);
	std::list<GameObject*> gameObjectList;
};