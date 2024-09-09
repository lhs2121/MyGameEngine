#include "Pre.h"
#include "GameObject.h"

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

void GameObject::ChildUpdate(float _deltaTime)
{
	Update(_deltaTime);

	for (Object* Child : componentList)
	{
		Child->Update(_deltaTime);
	}

	for (GameObject* Child : childList)
	{
		Child->ChildUpdate(_deltaTime);
	}
}

void GameObject::SetParent(GameObject* _pParent)
{
	if (pParent != nullptr)
	{
		GameObject* pCastParent = (GameObject*)pParent;

		pCastParent->childList.remove(this);

		pParent->transform.childTransformList.remove(&this->transform);
	}

	_pParent->childList.push_back(this);

	pParent = _pParent;

	_pParent->transform.childTransformList.push_back(&transform);

	transform.parentTransform = &_pParent->transform;
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
