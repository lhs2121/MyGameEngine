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

	virtual void OnCollisionEnter(Colider* _Other) {};
	virtual void OnCollisionStay(Colider* _Other) {};
	virtual void OnCollisionExit(Colider* _Other) {};

	void         AllStart();
		         
	void         AllUpdate(float _deltaTime);
		             
	void         AllEnd();
		         
	void         AllRelease();

	void         Enable() { isEnable = true; }
	void         Disenable() { isEnable = false; }

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
		newComp->m_pRenderer = m_pRenderer;
		newComp->m_pInputObject = m_pInputObject;
		transform.TransformUpdate();
		newComp->Awake();
		return (T*)newComp;
	}

	void RemoveChild(Object* pChild);

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
	IRenderer* m_pRenderer = nullptr;
	IInputObject* m_pInputObject;
protected:
	int order = 0;
	bool death = false;
	bool isEnable = true;
	Object* parent = nullptr;
	std::list<Object*> childs;
};

