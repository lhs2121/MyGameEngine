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
		Component* newComp = new T();
		newComp->SetMainObject(mainInput, mainWindow, mainDevice, mainResManager);
		newComp->pParent = this;
		newComp->Awake();

		transform.childTransformList.push_back(&newComp->transform);
		newComp->transform.parentTransform = &transform;

		componentList.push_back(newComp);
		return (T*)newComp;
	}

	template<typename T>
	T* GetComponent()
	{
		for(Component* comp : componentList)
		{
			T* castComp = dynamic_cast<T*>(comp);
			if (nullptr != castComp)
			{
				return castComp;
			}
		}
		return nullptr;
	}

	void ChildUpdate(float _deltaTime);
	void SetParent(GameObject* _pParent);

	GameObject* GetChild(int _num);
	GameObject* GetChild(const char* _name);

private:
	std::list<Component*> componentList;
	std::list<GameObject*> childList;
};