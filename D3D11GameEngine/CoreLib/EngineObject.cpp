#include "Pre.h"
#include "EngineObject.h"

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

EngineObject* EngineObject::GetTopParent()
{
	if (Parent != nullptr)
	{
		return Parent->GetTopParent();
	}
	return this;
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


