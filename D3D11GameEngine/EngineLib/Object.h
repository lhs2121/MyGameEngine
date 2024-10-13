#pragma once
#include <common\declspec.h>
#include <map>
#include "Transform.h"

class Scene;
class Colider;
class Object
{
public:
	Object();
	virtual ~Object();

	virtual void Awake() {}

	virtual void Start() {}

	virtual void Update(float _deltaTime) {}

	virtual void End() {}

	virtual void Release() {}

	void         AllStart();
		         
	void         AllUpdate(float _deltaTime);
		             
	void         AllEnd();
		         
	void         AllRelease();

	void         SetName(base::string _name) { name = _name; }

	void         SetParent(Object* _parent);

	void         Destroy();
	         	                 
	Object*      GetParent() { return parent; }
		         
	bool         GetDeath() const { return death; }
		         
	Scene*       GetScene();
		         		         
	bool         GetKeyDown(int _key);
		         
	bool         GetKeyPress(int _key);
		         
	bool         GetKeyUp(int _key);
		         
	bool         GetKeyFree(int _key);

	template<typename T>
	T* CreateChild(int order = 0)
	{
		Object* newComp = new T();
		newComp->SetParent(this);
		newComp->Awake();
		transform.TransformUpdate();
		return (T*)newComp;
	}

	template<typename T>
	T* GetChild()
	{
		for (Object* child : childs)
		{
			T* result = dynamic_cast<T*>(child); 
			if (result != nullptr)
			{
				return result;
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
	std::list<Object*> childs;
};

