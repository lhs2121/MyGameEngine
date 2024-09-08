#pragma once
#include <common\declspec.h>
#include "Transform.h"
// Ό³Έν :
class Level;
class Object
{
public:
	Object();
	virtual ~Object();

	void DeleteAllChild();
	void SetName(EngineString _Name)
	{
		Name = _Name;
	}

	void SetParent(Object* _Parent);

	Level* GetLevel();

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

	Object* CreateObject(Object* _NewActor);
	Object* GetChild(int _ChildNumber);
	Object* GetChild(const char* _ChildName);

	Transform Transform;
	EngineString Name;


	IEngineInput* Input = nullptr;
	IEngineWindow* Window = nullptr;
	IDevice* Device = nullptr;
	IResManager* ResManager = nullptr;
protected:
	bool Death = false;

	std::list<Object*> ChildList;
	Object* Parent = nullptr;
};