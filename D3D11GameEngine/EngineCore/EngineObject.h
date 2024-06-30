#pragma once
#include "EngineTransform.h"
// 설명 :
class EngineObject
{
public:
	// constrcuter destructer
	EngineObject();
	virtual ~EngineObject();

	// delete Function
	EngineObject(const EngineObject& _Other) = delete;
	EngineObject(EngineObject&& _Other) noexcept = delete;
	EngineObject& operator=(const EngineObject& _Other) = delete;
	EngineObject& operator=(EngineObject&& _Other) noexcept = delete;

	void SetName(EngineString _Name)
	{
		Name = _Name;
	}

	void SetParent(EngineObject* _Parent)
	{
		_Parent->SetChild(this);
	}

	void DetachParent()
	{
		Parent->DetachChild(this);
	}

	void SetChild(EngineObject* _Child)
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

	void DetachChild(EngineObject* _Child)
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

	EngineObject* GetChild(int Order = 0)
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

	EngineObject* GetTopParent()
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

	bool Destroy()
	{
		Death = true;
	}

	bool IsDeath()
	{
		return Death;
	}

	virtual void Start();
	void ChildUpdate(float _Delta);
	virtual void Update(float _Delta);
	virtual void Release();

	EngineTransform Transform;
protected:
	EngineObject* Parent = nullptr;
	std::list<EngineObject*> ChildList;
	EngineString Name;
	bool Death = false;
};