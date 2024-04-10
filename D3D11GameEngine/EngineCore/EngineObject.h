#pragma once
#include "EngineTransform.h"

// Ό³Έν :
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

	void SetName(std::string _Name)
	{
		Name = _Name;
	}

	void SetParent(EngineObject* _Parent)
	{
		_Parent->PushChild(this);
	}

	void PushChild(EngineObject* _Child)
	{
		ChildList.push_back(_Child);
		_Child->Parent = this;
	}

	EngineObject* GetChild(int Order = 0)
	{
		std::list<EngineObject*>::iterator Start = ChildList.begin();
		std::list<EngineObject*>::iterator End = ChildList.end();

		EngineObject* Result = nullptr;
		for (int i = 0; i <= Order; i++)
		{
			if (i == Order)
			{
				Result = (*Start);
				return Result;
			}
			Start++;
		}

		return Result;
	}
	virtual void Start();
	virtual void Update(float _Delta);
	virtual void Release();

private:
	EngineObject* Parent = nullptr;
	std::list<EngineObject*> ChildList;

	EngineTransform Transform;
	std::string Name;
};