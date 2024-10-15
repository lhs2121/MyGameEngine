#pragma once
#include "Object.h"
#include "Camera.h"
#include "Colider.h"
#include "QuadTree.h"
class Scene : public Object
{
public:
	Scene();
	~Scene();

	void      Render();
	void      CreateCamera();
	void      IntoQuadTree(Colider* pCol);
	void      AllCollision();
	void      CheckDeath();

	Camera*   GetMainCamera();

	CQuadTree* quRoot;
	std::vector<CQuadTree*> quTails;
	std::vector<Colider*> allColider;
	std::vector<Object*> deathNote;
private:
	std::list<Camera*> cameraList;
};

