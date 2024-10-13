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

void Object::AllDeath()
{
	std::vector<Object*> deathNote;
	for (Object* child : childs)
	{
		if (child->death)
		{
			deathNote.push_back(child);
		}
	}

	for (Object* o : deathNote)
	{
		childs.remove(o);
		delete o;
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
	return Input::IsDown(_key, this);
}

bool Object::GetKeyPress(int _key)
{
	return Input::IsPress(_key, this);
}

bool Object::GetKeyUp(int _key)
{
	return Input::IsUp(_key, this);
}

bool Object::GetKeyFree(int _key)
{
	return Input::IsFree(_key, this);
}

	
