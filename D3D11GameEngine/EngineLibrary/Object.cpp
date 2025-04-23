#include "pch.h"
#include "Object.h"
#include "Scene.h"

Object::Object()
{
}

Object::~Object()
{
	for (Object* child : m_pChildList)
	{
		delete child;
	}
	m_pChildList.clear();
}

void Object::AllStart()
{
	Start();

	for (Object* child : m_pChildList)
	{
		child->AllStart();
	}
}

void Object::AllUpdate(float _deltaTime)
{
	if (!m_bEnable)
		return;

	m_transform.TransformUpdate();
	Update(_deltaTime);

 	for (Object* child : m_pChildList)
	{
		child->AllUpdate(_deltaTime);
	}
}

void Object::AllEnd()
{
	End();

	for (Object* child : m_pChildList)
	{
		child->AllEnd();
	}
}

void Object::AllRelease()
{
	Release(); 

	for (Object* child : m_pChildList)
	{
		child->AllRelease();
	}
}

void Object::SetParent(Object* _m_pParent)
{
	if (m_pParent != nullptr)
	{
		m_pParent->m_pChildList.remove(this);
	}

	_m_pParent->m_pChildList.push_back(this);
	m_pParent = _m_pParent;

	m_transform.SetParent(&m_pParent->m_transform);
}

void Object::Destroy()
{
	Scene* m_pParentScene = GetScene();
	m_pParentScene->m_pDeathObjectList.push_back(this);
	m_bDeath = true;
}

Scene* Object::GetScene()
{
	if (m_pParent == nullptr)
	{
		return (Scene*)this;
	}

	return m_pParent->GetScene();
}

bool Object::GetKeyDown(int _key)
{
	return m_pInputObject->IsDown(_key, this);
}

bool Object::GetKeyPress(int _key)
{
	return m_pInputObject->IsPress(_key, this);
}

bool Object::GetKeyUp(int _key)
{
	return m_pInputObject->IsUp(_key, this);
}

bool Object::GetKeyFree(int _key)
{
	return m_pInputObject->IsFree(_key, this);
}

void Object::RemoveChild(Object* pChild)
{
	m_pChildList.remove(pChild);
}

	
