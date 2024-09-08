#pragma once
#include "Object.h"
#include "Component.h"

class GameObject : public Object
{
public:
	GameObject();
	~GameObject();

	bool GetKeyDown(int _key)
	{
		return mainInput->IsDown(_key, this);
	}
	bool GetKeyPress(int _key)
	{
		return mainInput->IsPress(_key, this);
	}
	bool GetKeyUp(int _key)
	{
		return mainInput->IsUp(_key, this);
	}
	bool GetKeyFree(int _key)
	{
		return mainInput->IsFree(_key, this);
	}

	template<typename T>
	T* AddComponent()
	{
		Component* newComponent = new T();
		newComponent->SetMainObject(mainInput, mainWindow, mainDevice, mainResManager);
		newComponent->pParent = this;
		newComponent->Awake();

		transform.childTransformList.push_back(&newComponent->transform);
		newComponent->transform.parentTransform = &transform;

		ComponentList.push_back(newComponent);
		return (T*)newComponent;
	}

	void ChildUpdate(float _deltaTime);
	void SetParent(GameObject* _pParent);

	GameObject* GetChild(int _num);
	GameObject* GetChild(const char* _name);


	std::list<Component*> ComponentList;
	std::list<GameObject*> ChildList;
};