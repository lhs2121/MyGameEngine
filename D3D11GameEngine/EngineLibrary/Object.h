#pragma once
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

	void         Enable() { m_bEnable = true; }
	void         Disenable() { m_bEnable = false; }

	void         SetName(base::string _name) { m_name = _name; }

	void         SetParent(Object* _m_pParent);

	void         Destroy();
	         	                 
	Object*      GetParent() { return m_pParent; }
		         
	bool         GetDeath() const { return m_bDeath; }
		         
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
		m_transform.TransformUpdate();
		newComp->Awake();
		return (T*)newComp;
	}

	void RemoveChild(Object* pChild);

	template<typename T>
	T* GetChild()
	{
		for (Object* child : m_pChildList)
		{
			T* result = dynamic_cast<T*>(child); 
			if (result != nullptr)
			{
				return result;
			}
		}
		return nullptr;
	}

	base::string m_name;
	Transform m_transform;
	IRenderer* m_pRenderer;
	IInputObject* m_pInputObject;
protected:
	int m_order = 0;
	bool m_bDeath = false;
	bool m_bEnable = true;
	Object* m_pParent = nullptr;
	std::list<Object*> m_pChildList;
};

