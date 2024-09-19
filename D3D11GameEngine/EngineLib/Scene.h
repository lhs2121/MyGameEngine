#pragma once
#include "Object.h"
#include "Camera.h"
#include "Colider.h"

class Scene : public Object
{
public:
	Scene();

	void      Render();

	void      Collision(float _deltaTime);

	void      CreateCamera();

	void      AddCollision(Colider* _col);

	Camera*   GetMainCamera();
private:
	std::list<Camera*> cameraList;
	std::vector<Colider*> collisionList;
};

