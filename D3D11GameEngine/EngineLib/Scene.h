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
	void      AddCollision(Colider* pCol);
	void      UpdateQuadTree();
	void      CheckDeath();

	Camera*   GetMainCamera();

	CQuadTree* pQuadRoot = nullptr;
	std::vector<Colider*> dynamicColiders;
	std::vector<Object*> deathNote;
private:
	std::list<Camera*> cameraList;
};

