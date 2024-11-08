#pragma once
#include "Object.h"

struct ICollision;
struct IQuadTree;
class Scene : public Object
{
public:
	void UseQuadTree();
	void CheckDeath();

	bool isUseQuadTree = false;
	IQuadTree* pQuad;
	std::vector<Object*> deathNote;
};

