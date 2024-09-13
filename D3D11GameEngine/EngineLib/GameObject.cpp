#include "Pre.h"
#include "GameObject.h"
#include "Scene.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	for (GameObject* Child : childList)
	{
		delete Child;
	}
	for (Object* Child : componentList)
	{
		delete Child;
	}
}

bool GameObject::GetKeyDown(int _key)
{
	return Input::IsDown(_key, this);
}

bool GameObject::GetKeyPress(int _key)
{
	return Input::IsPress(_key, this);
}

bool GameObject::GetKeyUp(int _key)
{
	return Input::IsUp(_key, this);
}

bool GameObject::GetKeyFree(int _key)
{
	return Input::IsFree(_key,this);
}

void GameObject::AllStart()
{
	Start();

	for (Object* Child : componentList)
	{
		Child->Start();
	}

	for (GameObject* Child : childList)
	{
		Child->AllStart();
	}
}

void GameObject::AllUpdate(float _deltaTime)
{
	Update(_deltaTime);

	for (Object* Child : componentList)
	{
		Child->Update(_deltaTime);
	}

	for (GameObject* Child : childList)
	{
		Child->AllUpdate(_deltaTime);
	}
}

void GameObject::SetParent(GameObject* _parent)
{
	if (parentObject != nullptr)
	{
		if ((void*)parentObject == (void*)scene)
		{
			scene->DeleteGameObject(this);
		}
		else
		{
			GameObject* castObj = (GameObject*)parentObject;
			castObj->childList.remove(this);
		}
	}

	parentObject = (Object*)_parent;
	_parent->childList.push_back(this);
	transform.SetParent(&_parent->transform);
}

GameObject* GameObject::GetChild(int _num)
{
	size_t Count = childList.size();

	if (Count == 0)
	{
		return nullptr;
	}

	if (Count < _num)
	{
		return nullptr;
	}

	auto iter = childList.begin();
	std::advance(iter, _num);

	return *iter;
}

GameObject* GameObject::GetChild(const char* _name)
{
	for (GameObject* Child : childList)
	{
		if (Child->name == _name)
		{
			return Child;
		}
	}

	return nullptr;
}
