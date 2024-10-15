#pragma once
#include "Object.h"
#include "Camera.h"
#include "Colider.h"
class Scene : public Object
{
public:
	Scene();
	~Scene();

	void      Render();
	void      CreateCamera();

	void      CheckDeath();

	Camera*   GetMainCamera();

	std::vector<Colider*> allColider;
	std::vector<Object*> deathNote;
private:
	std::list<Camera*> cameraList;
};

