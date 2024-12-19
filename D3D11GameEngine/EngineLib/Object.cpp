#include "Pre.h"
#include "Object.h"
#include "Scene.h"

Object::Object()
{
}

Object::~Object()
{
	for (Object* child : childs)
	{
		delete child;
	}
	childs.clear();
}

void Object::AllStart()
{
	Start();

	for (Object* child : childs)
	{
		child->AllStart();
	}
}

void Object::AllUpdate(float _deltaTime)
{
	if (!isEnable)
		return;

	Update(_deltaTime);

 	for (Object* child : childs)
	{
		child->AllUpdate(_deltaTime);
	}
}

void Object::AllEnd()
{
	End();

	for (Object* child : childs)
	{
		child->AllEnd();
	}
}

void Object::AllRelease()
{
	Release(); 

	for (Object* child : childs)
	{
		child->AllRelease();
	}
}

void Object::SetParent(Object* _parent)
{
	if (parent != nullptr)
	{
		parent->childs.remove(this);
	}

	_parent->childs.push_back(this);
	parent = _parent;

	transform.SetParent(&parent->transform);
}

void Object::Destroy()
{
	Scene* ParentScene = GetScene();
	ParentScene->deathNote.push_back(this);
	death = true;
}

Scene* Object::GetScene()
{
	if (parent == nullptr)
	{
		return (Scene*)this;
	}

	return parent->GetScene();
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
	childs.remove(pChild);
}

	
