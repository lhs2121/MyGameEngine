#pragma once
#include "Object.h"
#include "Component.h"

class GameObject : public Object
{
public:
	GameObject();
	~GameObject();

	bool GetKeyDown(int _key);
	bool GetKeyPress(int _key);
	bool GetKeyUp(int _key);
	bool GetKeyFree(int _key);

	template<typename T>
	T* AddComponent()
	{
		Component* newComp = new T();
		newComp->parentObject = this;
		newComp->scene = scene;

		newComp->Awake();
		newComp->transform.SetParent(&transform);

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

	std::vector<Component*> GetComponents()
	{
		std::vector<Component*> comps;
		size_t compSize = componentList.size();
		comps.reserve(compSize);

		for (Component* comp : componentList)
		{
			comps.push_back(comp);
		}
		return comps;
	}

	void AllStart();
	void AllUpdate(float _deltaTime);
	void SetParent(GameObject* _parent);

	GameObject* GetChild(int _num);
	GameObject* GetChild(const char* _name);

	int objectOrder;
private:
	std::list<Component*> componentList;
	std::list<GameObject*> childList;
};