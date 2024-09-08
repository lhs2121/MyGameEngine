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
		newGameObject->SetMainObject(mainInput, mainWindow, mainDevice, mainResManager);
		newGameObject->pParent = this;
		newGameObject->Awake();

		allGameObject.insert({ _order,newGameObject });

		return (T*)newGameObject;
	}

	void      CreateCamera();
	void      AddCollision(Colider2D* _col);
	Camera*   GetMainCamera();
private:

	std::map<int, GameObject*> allGameObject;
	std::list<Camera*> cameraList;
	std::list<Colider2D*> collisionList;
};

