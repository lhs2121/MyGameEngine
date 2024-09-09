#pragma once
#include "Object.h"
#include "GameObject.h"
#include "Camera.h"
#include "Colider2D.h"

class Level : public Object
{
public:
	Level();
	~Level();

	void Start() override;
	void AllGameObjectUpdate(float _deltaTime);
	void Update(float _deltaTime) override;
	void Render();

	template<class T>
	T* CreateGameObject(int _order = 0)
	{
		GameObject* newGameObject = new T();
		newGameObject->pParent = this;
		newGameObject->SetMainObject(mainInput, mainWindow, mainDevice, mainResManager);
		newGameObject->Awake();

		if (allGameObject.find(_order) == allGameObject.end())
		{
			std::list<GameObject*> newGameObjectList;
			allGameObject.insert({ _order,std::move(newGameObjectList) });
		}

		allGameObject[_order].push_back(newGameObject);
		return (T*)newGameObject;
	}

	void      CreateCamera();
	void      AddCollision(Colider2D* _col);
	Camera*   GetMainCamera();
private:

	std::map<int, std::list<GameObject*>> allGameObject;
	std::list<Camera*> cameraList;
	std::list<Colider2D*> collisionList;
};

