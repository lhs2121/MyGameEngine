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

	void SetName(EngineString _Name);
	void SetParent(EngineObject* _Parent);
	void DetachParent();
	void SetChild(EngineObject* _Child);
	void DetachChild(EngineObject* _Child);
	EngineObject* GetChild(int Order = 0);
	EngineObject* GetTopParent();
	void Destroy();
	bool IsDeath();
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