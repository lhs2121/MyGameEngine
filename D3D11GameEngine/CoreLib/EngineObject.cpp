#include "Pre.h"
#include "EngineObject.h"
#include "EngineLevel.h"

EngineObject::EngineObject()
{
}

EngineObject::~EngineObject()
{
}

void EngineObject::DeleteAllChild()
{
	for (EngineObject* Child : ChildList)
	{
		Child->DeleteAllChild();
		delete Child;
	}
}

void EngineObject::SetParent(EngineObject* _Parent)
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

EngineLevel* EngineObject::GetLevel()
{
	if (Parent != nullptr)
	{
		return Parent->GetLevel();
	}
	return (EngineLevel*)this;
}

void EngineObject::ChildUpdate(float _Delta)
{
	for (EngineObject* Child : ChildList)
	{
		Child->ChildUpdate(_Delta);
		Child->Update(_Delta);
	}
}

EngineObject* EngineObject::CreateObject(EngineObject* _NewActor)
{
	_NewActor->Input = Input;
	_NewActor->Window = Window;
	_NewActor->Device = Device;
	_NewActor->ResManager = ResManager;
	_NewActor->SetParent(this);
	_NewActor->Awake();
	return _NewActor;
}

EngineObject* EngineObject::GetChild(int _ChildNumber)
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

EngineObject* EngineObject::GetChild(const char* _ChildName)
{
	for (EngineObject* Child : ChildList)
	{
		if (Child->Name == _ChildName)
		{
			return Child;
		}
	}

	return nullptr;
}


