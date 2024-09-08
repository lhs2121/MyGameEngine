#include "Pre.h"
#include "Object.h"
#include "Level.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::DeleteAllChild()
{
	for (Object* Child : ChildList)
	{
		Child->DeleteAllChild();
		delete Child;
	}
}

void Object::SetParent(Object* _Parent)
{
	if (Parent != nullptr)
	{
		Parent->ChildList.remove(this);
		Parent->Transform.ChildTransformList.remove(&this->Transform);
	}
	_Parent->ChildList.push_back(this);
	Parent = _Parent;

	_Parent->Transform.ChildTransformList.push_back(&Transform);
	Transform.ParentTransform = &_Parent->Transform;
}

Level* Object::GetLevel()
{
	if (Parent != nullptr)
	{
		return Parent->GetLevel();
	}
	return (Level*)this;
}

void Object::ChildUpdate(float _Delta)
{
	for (Object* Child : ChildList)
	{
		Child->ChildUpdate(_Delta);
		Child->Update(_Delta);
	}
}

Object* Object::CreateObject(Object* _NewActor)
{
	_NewActor->Input = Input;
	_NewActor->Window = Window;
	_NewActor->Device = Device;
	_NewActor->ResManager = ResManager;
	_NewActor->SetParent(this);
	_NewActor->Awake();
	return _NewActor;
}

Object* Object::GetChild(int _ChildNumber)
{
	size_t Count = ChildList.size();

	if (Count == 0)
	{
		return nullptr;
	}

	if (Count < _ChildNumber)
	{
		return nullptr;
	}

	auto iter = ChildList.begin();
	std::advance(iter, _ChildNumber);

	return *iter;
}

Object* Object::GetChild(const char* _ChildName)
{
	for (Object* Child : ChildList)
	{
		if (Child->Name == _ChildName)
		{
			return Child;
		}
	}

	return nullptr;
}


