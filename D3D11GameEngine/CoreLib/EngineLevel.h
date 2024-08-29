#pragma once
#include "EngineObject.h"

class EngineCollision;
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
	void            AddCollision(EngineCollision* _Col);
	EngineCamera*   GetMainCamera();
private:
	EngineList CameraList;
	EngineList CollisionList;
};

