#pragma once
#include <list>
#include "GameObject.h"
class Level
{
public:
	virtual void Init() {};
	virtual void Start() {};
	virtual void Update(float deltaTime) {};
	virtual void End() {};

	GameObject* CreateGameObject();
	void UpdateGameObjects(float deltaTime);
	void ReleaseGameObjects();
	std::list<GameObject*> gameObjectList;
	IRenderer* renderer = nullptr;
	IInputObject* input = nullptr;

private:
	virtual ~Level() {};
};