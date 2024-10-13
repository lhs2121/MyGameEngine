#pragma once
#include "Object.h"
#include "Camera.h"
#include "ColGroup.h"

class Scene : public Object
{
public:
	Scene();
	~Scene();

	void      Render();

	ColGroup* GetGroup(int _order);
	void      SetColOrder(Colider* _col,int _order);
	void      CreateCamera();

	void      CheckDeath();
	void      AddCollision(Colider* _col);

	Camera*   GetMainCamera();

	std::vector<Object*> deathNote;
private:
	std::map<int, ColGroup*> colGroups;
	std::list<Camera*> cameraList;
};

