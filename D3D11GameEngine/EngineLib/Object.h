#pragma once
#include <common\declspec.h>
#include "Transform.h"

class Scene;
class Object
{
public:
	Object();
	virtual ~Object();

	void SetMainObject(IEngineInput* _mainInput, IEngineWindow* _mainWindow, IDevice* _mainDevice)
	{
		mainInput = _mainInput;
		mainWindow = _mainWindow;
		mainDevice = _mainDevice;
	}

	void SetName(EngineString _name) { name = _name; }

	void Destroy() { death = true; }

	bool IsDeath() const { return death; }

	virtual void Awake() {}

	virtual void Start() {}

	virtual void Update(float _deltaTime) {}

	virtual void End() {}

	virtual void Release() {}

	EngineString name;
	Transform transform;
	Object* parentObject = nullptr;
	Scene* scene = nullptr;
protected:
	IEngineInput* mainInput = nullptr;
	IEngineWindow* mainWindow = nullptr;
	IDevice* mainDevice = nullptr;
	 

	bool death = false;
};

