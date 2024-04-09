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
		Parent = _Parent;
	}

	void SetChild(EngineObject* _Child)
	{
		Child = _Child;
		Child->SetParent(this);

		Transform.SetChild(&Child->Transform);
	}

	virtual void Start();
	virtual void Update(float _Delta);
	virtual void Release();

private:
	EngineObject* Parent = nullptr;
	EngineObject* Child = nullptr;

	EngineTransform Transform;
	std::string Name;
};