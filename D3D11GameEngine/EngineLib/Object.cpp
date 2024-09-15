#include "Pre.h"
#include "Object.h"
#include "Scene.h"

Object::Object()
{
}

Object::~Object()
{
	for (auto& pair : childs)
	{
		std::list<Object*>& objectList = pair.second;

		for (Object* object : objectList)
		{
			delete object;
		}
		objectList.clear();
	}
	childs.clear();
}

void Object::ChildStart()
{
	Start();

	for (auto& pair : childs)
	{
		std::list<Object*>& objectList = pair.second;

		for (Object* object : objectList)
		{
			object->Start();
			object->ChildStart();
		}
	}
}

void Object::ChildUpdate(float _deltaTime)
{
	Update(_deltaTime);

	for (auto& pair : childs)
	{
		std::list<Object*>& objectList = pair.second;

		for (Object* object : objectList)
		{
			object->Update(_deltaTime);
			object->ChildUpdate(_deltaTime);
		}
	}
}

void Object::ChildLateUpdate(float _deltaTime)
{
	LateUpdate(_deltaTime);

	for (auto& pair : childs)
	{
		std::list<Object*>& objectList = pair.second;

		for (Object* object : objectList)
		{
			object->LateUpdate(_deltaTime);
			object->ChildLateUpdate(_deltaTime);
		}
	}
}

void Object::ChildEnd()
{
	End();

	for (auto& pair : childs)
	{
		std::list<Object*>& objectList = pair.second;

		for (Object* object : objectList)
		{
			object->End();
			object->ChildEnd();
		}
	}
}

void Object::ChildRelease()
{
	Release();

	for (auto& pair : childs)
	{
		std::list<Object*>& objectList = pair.second;

		for (Object* object : objectList)
		{
			object->ChildRelease();
		}
	}
}

void Object::ChildDestroy()
{
	for (auto& pair : childs)
	{
		std::list<Object*>& objectList = pair.second;

		auto it = objectList.begin();
		auto end = objectList.end();
		for (; it != end; it++)
		{
			if ((*it)->death)
			{
				(*it)->ChildRelease();
				delete *it;
				it = objectList.erase(it);
			}

		}
	}
}

void Object::SetOrder(int _order)
{
	if (parent != nullptr)
	{
		parent->childs[order].remove(this);
		parent->childs[_order].push_back(this);
	}
	order = _order;
}

void Object::SetParent(Object* _parent)
{
	if (parent != nullptr)
	{
		parent->childs[order].remove(this);
	}

	parent = _parent;
	parent->childs[0].push_back(this);

	transform.SetParent(&parent->transform);
}

Scene* Object::GetScene()
{
	if (parent == nullptr)
	{
		return (Scene*)this;
	}

	parent->GetScene();
}

