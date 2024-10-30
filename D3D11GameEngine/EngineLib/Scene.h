#pragma once
#include "Object.h"
#include "Colider.h"
#include "QuadTree.h"
class Scene : public Object
{
public:
	void      AddCollision(Colider* pCol);
	void      UpdateQuadTree();
	void      CheckDeath();

	CQuadTree* pQuadRoot = nullptr;
	std::vector<Colider*> dynamicColiders;
	std::vector<Object*> deathNote;
};

