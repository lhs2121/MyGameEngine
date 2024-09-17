#pragma once
#include <common\declspec.h>
#include "Transform.h"

class Scene;
class Object
{
public:
	Object();
	virtual ~Object();

	virtual void Awake() {}

	virtual void Start() {}

	virtual void Update(float _deltaTime) {}

	virtual void LateUpdate(float _deltaTime) {}

	virtual void End() {}

	virtual void Release() {}

	void ChildStart();

	void ChildUpdate(float _deltaTime);

	void ChildLateUpdate(float _deltaTime);

	void ChildEnd();

	void ChildRelease();

	void ChildDestroy();


	void SetName(base::string _name) { name = _name; }

	void Destroy() { death = true; }
	bool IsDeath() const { return death; }

	void SetOrder(int _order);

	void SetParent(Object* _parent);
	Object* GetParent() { return parent; }

	Scene* GetScene();

	bool GetKeyDown(int _key);
	bool GetKeyPress(int _key);
	bool GetKeyUp(int _key);
	bool GetKeyFree(int _key);

	template<typename T>
	T* CreateChild(int order = 0)
	{
		Object* newComp = new T();
		newComp->SetOrder(order);
		newComp->SetParent(this);
		newComp->Awake();
		newComp->transform.TransformUpdate();
		return (T*)newComp;
	}

	template<typename T>
	T* GetChild()
	{
		for (auto& pair : childs)
		{
			std::list<Object*> objectList = pair.second;

			for (Object* object : objectList)
			{
				T* result = dynamic_cast<T*>(object);
				if (result != nullptr)
				{
					return result;
				}
			}
		}
		return nullptr;
	}
	base::string name;
	Transform transform;

private:
	int order = 0;
	bool death = false;
	Object* parent = nullptr;
	std::map<int, std::list<Object*>> childs;
};

