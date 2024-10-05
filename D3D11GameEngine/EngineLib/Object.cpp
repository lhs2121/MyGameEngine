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

void Object::AllStart()
{
	Start();

	for (auto& pair : childs)
	{
		std::list<Object*>& objectList = pair.second;

		for (Object* object : objectList)
		{
			object->AllStart();
		}
	}
}

void Object::AllUpdate(float _deltaTime)
{
	Update(_deltaTime);

	for (auto& pair : childs)
	{
		std::list<Object*>& objectList = pair.second;

		for (Object* object : objectList)
		{
			object->AllUpdate(_deltaTime);
		}
	}
}

void Object::AllLateUpdate(float _deltaTime)
{
	LateUpdate(_deltaTime);

	for (auto& pair : childs)
	{
		std::list<Object*>& objectList = pair.second;

		for (Object* object : objectList)
		{
			object->AllLateUpdate(_deltaTime);
		}
	}
}

void Object::AllEnd()
{
	End();

	for (auto& pair : childs)
	{
		std::list<Object*>& objectList = pair.second;

		for (Object* object : objectList)
		{
			object->AllEnd();
		}
	}
}

void Object::AllRelease()
{
	Release();

	for (auto& pair : childs)
	{
		std::list<Object*>& objectList = pair.second;

		for (Object* object : objectList)
		{
			object->AllRelease();
		}
	}
}

void Object::AllDeath()
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
				(*it)->AllRelease();
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

void Object::TransformUpdate()
{
	transform.vecWorldScale = transform.vecRecievedScale * transform.vecLocalScale;
	transform.vecWorldRotation = transform.vecRecievedRotation + transform.vecLocalRotation;
	transform.vecWorldPosition = transform.vecRecievedPosition + transform.vecLocalPosition;

	for (auto& pair : childs)
	{
		auto& list = pair.second;
		for (Object* o : list)
		{
			o->transform.vecRecievedScale = transform.vecWorldScale;
			o->transform.vecRecievedRotation = transform.vecWorldRotation;
			o->transform.vecRecievedPosition = transform.vecWorldPosition;
			o->TransformUpdate();
		}
	}

	transform.matWorldScale = XMMatrixScalingFromVector(transform.vecWorldScale);
	transform.matWorldRotation = XMMatrixRotationRollPitchYawFromVector(transform.vecWorldRotation);
	transform.matWorldPosition = XMMatrixTranslationFromVector(transform.vecWorldPosition);
	transform.quatWorld = XMQuaternionRotationMatrix(transform.matWorldRotation);
	transform.matWorld = transform.matWorldScale * transform.matWorldRotation * transform.matWorldPosition;
}
