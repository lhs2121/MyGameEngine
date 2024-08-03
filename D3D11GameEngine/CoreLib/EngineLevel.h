#pragma once

#include "EngineObject.h"

class EngineCamera;
class EngineActor;
class CoreAPI EngineLevel : public EngineObject
{
public:
	EngineLevel();
	~EngineLevel();

	void Start() override;
	void Update(float _Delta) override;
	void Render();

	void*           CreateActor(void* _NewActor);
	EngineCamera*   GetMainCamera();
private:
	EngineList CameraList;
};

