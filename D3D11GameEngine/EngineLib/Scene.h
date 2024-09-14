#pragma once
#include "Object.h"
#include "Camera.h"
#include "Colider2D.h"

class Scene : public Object
{
public:
	Scene();

	void      Render();

	void      Collision(float _deltaTime);

	void      CreateCamera();

	void      AddCollision(Colider2D* _col);

	Camera*   GetMainCamera();
private:
	std::list<Camera*> cameraList;
	std::vector<Colider2D*> collisionList;
};

