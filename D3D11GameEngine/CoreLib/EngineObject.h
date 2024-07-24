#pragma once
#include <common\declspec.h>
#include "EngineTransform.h"
// Ό³Έν :
class CoreAPI EngineObject
{
public:
	EngineObject();
	virtual ~EngineObject();

	void SetName(EngineString _Name);

	void SetParent(EngineObject* _Parent);

	EngineObject* GetTopParent();

	void Destroy();

	bool IsDeath();

	void ChildUpdate(float _Delta);

	virtual void Awake();

	virtual void Start();

	virtual void Update(float _Delta);

	virtual void End();

	virtual void Release();

	EngineTransform Transform;
protected:
	EngineList ChildList;
	EngineObject* Parent = nullptr;
	EngineString Name;

	bool Death = false;
};