#pragma once
#include <common\declspec.h>
#include "Transform.h"

class Scene;
class Object
{
public:
	Object();
	virtual ~Object();

	void SetMainObject(IEngineInput* _mainInput, IEngineWindow* _mainWindow, IDevice* _mainDevice, IResManager* _mainResManager)
	{
		mainInput = _mainInput;
		mainWindow = _mainWindow;
		mainDevice = _mainDevice;
		mainResManager = _mainResManager;
	}

	void SetName(EngineString _name) { name = _name; }

	Scene* GetScene();

	void Destroy() { death = true; }

	bool IsDeath() { return death; }

	virtual void Awake() {}

	virtual void Start() {}

	virtual void Update(float _deltaTime) {}

	virtual void End() {}

	virtual void Release() {}

	EngineString name;
	Transform transform;
	Object* pParent = nullptr;

protected:
	IEngineInput* mainInput = nullptr;
	IEngineWindow* mainWindow = nullptr;
	IDevice* mainDevice = nullptr;
	IResManager* mainResManager = nullptr;

	bool death = false;
};

