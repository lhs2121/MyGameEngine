#pragma once
#include "Object.h"
#include "GameObject.h"
#include "Camera.h"
#include "Colider2D.h"

class Scene : public Object
{
public:
	Scene();
	~Scene();

	void Start() override;
	void Update(float _deltaTime) override;
	void Render();

	void AllGameObjectStart();
	void AllGameObjectUpdate(float _deltaTime);
	void AllCollisionUpdate(float _deltaTime);

	template<class T>
	T* CreateGameObject(int _order = 0)
	{
		GameObject* newGameObject = new T();
		newGameObject->parentObject = this;
		newGameObject->scene = this;
		newGameObject->objectOrder = _order;
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
	void      DeleteGameObject(GameObject* _gameObject);
	Camera*   GetMainCamera();
private:

	std::map<int, std::list<GameObject*>> allGameObject;
	std::list<Camera*> cameraList;
	std::list<Renderer*> collisionDebugRenderers;
	std::vector<Colider2D*> collisionList;
};

