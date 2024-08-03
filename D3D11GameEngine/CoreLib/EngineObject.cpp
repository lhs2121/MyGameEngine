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
	int Count = ChildList.GetCount();
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
	_Parent->ChildList.Add(this);
	Parent = _Parent;
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

	int Count = ChildList.GetCount();
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


