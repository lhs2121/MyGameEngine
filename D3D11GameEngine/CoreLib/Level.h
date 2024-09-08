#pragma once
#include "Object.h"
#include "Camera.h"
#include "Colider2D.h"

class Level : public Object
{
public:
	Level();
	~Level();

	void Start() override;
	void Update(float _Delta) override;
	void Render();

	void            CreateCamera();
	void            AddCollision(Colider2D* _Col);
	Camera*   GetMainCamera();
private:
	std::list<Camera*> CameraList;
	std::list<Colider2D*> CollisionList;
};

