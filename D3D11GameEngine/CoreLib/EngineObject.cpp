#include "Pre.h"
#include "EngineObject.h"

EngineObject::EngineObject()
{
}

EngineObject::~EngineObject()
{
	for (EngineObject* Child : ChildList)
	{
		if (Child != nullptr)
		{
			delete Child;
			Child = nullptr;
		}
	}
}

void EngineObject::SetName(EngineString _Name)
{
	Name = _Name;
}

void EngineObject::SetParent(EngineObject* _Parent)
{
	_Parent->SetChild(this);
}

void EngineObject::DetachParent()
{
	Parent->DetachChild(this);
}

void EngineObject::SetChild(EngineObject* _Child)
{
	// 이미 내 자식이라면 리턴
	for (EngineObject* Ptr : ChildList)
	{
		if (Ptr == _Child)
		{
			return;
		}
	}

	// 자식의 부모가 있다면 먼저 떼어놓기
	if (_Child->Parent != nullptr)
	{
		_Child->Parent->DetachChild(_Child);
	}
	ChildList.push_back(_Child);
	_Child->Parent = this;
}

void EngineObject::DetachChild(EngineObject* _Child)
{
	std::list<EngineObject*>::iterator Start = ChildList.begin();
	std::list<EngineObject*>::iterator End = ChildList.end();

	for (; Start != End;)
	{
		if ((*Start) == _Child)
		{
			ChildList.erase(Start);
			_Child->Parent = nullptr;
			return;
		}

		Start++;
	}
}

EngineObject* EngineObject::GetChild(int Order)
{
	std::list<EngineObject*>::iterator Start = ChildList.begin();
	std::list<EngineObject*>::iterator End = ChildList.end();

	EngineObject* Result = nullptr;
	int index = 0;
	for (; Start != End;)
	{
		if (index == Order)
		{
			Result = (*Start);
			return Result;
		}

		Start++;
		index++;
	}

	return Result;
}

EngineObject* EngineObject::GetTopParent()
{
	if (Parent != nullptr)
	{
		return Parent->GetTopParent();
	}
	else
	{
		return this;
	}
}

void EngineObject::Destroy()
{
	Death = true;
}

bool EngineObject::IsDeath()
{
	return Death;
}

void EngineObject::Start()
{
}

void EngineObject::ChildUpdate(float _Delta)
{
	for (EngineObject* Object : ChildList)
	{
		Object->Update(_Delta);
	}
}

void EngineObject::Update(float _Delta)
{

}

void EngineObject::Release()
{
}
