#pragma once
#include "EngineObject.h"
#include "EngineCamera.h"
#include "EngineCollision.h"

class EngineLevel : public EngineObject
{
public:
	EngineLevel();
	~EngineLevel();

	void Start() override;
	void Update(float _Delta) override;
	void Render();

	void            CreateCamera();
	void            AddCollision(EngineCollision* _Col);
	EngineCamera*   GetMainCamera();
private:
	std::list<EngineCamera*> CameraList;
	std::list<EngineCollision*> CollisionList;
};

