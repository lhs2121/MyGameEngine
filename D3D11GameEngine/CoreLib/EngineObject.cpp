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
	ChildList.GoFirst();
	UINT Count = ChildList.GetCount();
	for (size_t i = 0; i < Count; i++)
	{
		EngineObject* CurChild = (EngineObject*)ChildList.Item();
		CurChild->DeleteAllChild();

		delete CurChild;

		ChildList.GoNext();
	}
}

void EngineObject::SetName(EngineString _Name)
{
	Name = _Name;
}

void EngineObject::SetParent(EngineObject* _Parent)
{
	if (Parent != nullptr)
	{
		Parent->ChildList.Delete(this);
		Parent->Transform.ChildTransform.Delete(this);

		Parent = nullptr;
		Transform.ParentTransform = nullptr;
	}
	_Parent->ChildList.Add(this);
	Parent = _Parent;

	_Parent->Transform.ChildTransform.Add(&Transform);
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

void EngineObject::Destroy()
{
	Death = true;
}

bool EngineObject::IsDeath()
{
	return Death;
}

void EngineObject::ChildUpdate(float _Delta)
{
	ChildList.GoFirst();

	UINT Count = ChildList.GetCount();
	for (size_t i = 0; i < Count; i++)
	{
		EngineObject* CurChild = (EngineObject*)ChildList.Item();
		CurChild->ChildUpdate(_Delta);
		CurChild->Update(_Delta);

		ChildList.GoNext();
	}
}

void EngineObject::Awake()
{
}

void EngineObject::Start()
{
}

void EngineObject::Update(float _Delta)
{
}

void EngineObject::End()
{
	// 레벨이 끝나는 시점
}

void EngineObject::Release()
{
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
	ChildList.GoFirst();
	UINT Count = ChildList.GetCount();

	if (Count < _ChildNumber)
	{
		return nullptr;
	}

	for (UINT i = 0; i < _ChildNumber; i++)
	{
		ChildList.GoNext();
	}

	return (EngineObject*)ChildList.Item();
}

EngineObject* EngineObject::GetChild(const char* _ChildName)
{
	ChildList.GoFirst();
	UINT Count = ChildList.GetCount();
	for (UINT i = 0; i < Count; i++)
	{
		EngineObject* ChildObject = (EngineObject*)ChildList.Item();
		if (ChildObject->Name == _ChildName)
		{
			return ChildObject;
		}
		ChildList.GoNext();
	}
}


