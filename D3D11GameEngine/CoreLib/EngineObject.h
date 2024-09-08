#pragma once
#include <common\declspec.h>
#include "EngineTransform.h"
// Ό³Έν :
class EngineLevel;
class EngineObject
{
public:
	EngineObject();
	virtual ~EngineObject();

	void DeleteAllChild();
	void SetName(EngineString _Name)
	{
		Name = _Name;
	}

	void SetParent(EngineObject* _Parent);

	EngineLevel* GetLevel();

	void Destroy() 
	{ 
		Death = true; 
	}

	bool IsDeath() { return Death; }

	void ChildUpdate(float _Delta);

	virtual void Awake(){}

	virtual void Start(){}

	virtual void Update(float _Delta){}

	virtual void End(){}

	virtual void Release(){}

	EngineObject* CreateObject(EngineObject* _NewActor);
	EngineObject* GetChild(int _ChildNumber);
	EngineObject* GetChild(const char* _ChildName);

	EngineTransform Transform;
	EngineString Name;


	IEngineInput* Input = nullptr;
	IEngineWindow* Window = nullptr;
	IDevice* Device = nullptr;
	IResManager* ResManager = nullptr;
protected:
	bool Death = false;

	std::list<EngineObject*> ChildList;
	EngineObject* Parent = nullptr;
};