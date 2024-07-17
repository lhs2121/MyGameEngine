#pragma once
#include "CoreAPI.h"
#include "EngineTransform.h"
// Ό³Έν :
class EngineObject 
{
public:
	EngineObject();
	virtual ~EngineObject();
	void              SetName(EngineString _Name);

	void              SetParent(EngineObject* _Parent);

	void              DetachParent();

	void              SetChild(EngineObject* _Child);

	void              DetachChild(EngineObject* _Child);

	EngineObject*     GetChild(int Order = 0);

	EngineObject*     GetTopParent();

	void              Destroy();

	bool              IsDeath();

	virtual void      Awake();

	virtual void      Start();

	void              ChildUpdate(float _Delta);

	virtual void      Update(float _Delta);

	virtual void      Release();

	virtual void      End();
protected:
	std::list<EngineObject*> ChildList;
	EngineTransform Transform;
	EngineObject* Parent = nullptr;
	EngineString Name;

	bool Death = false;
};