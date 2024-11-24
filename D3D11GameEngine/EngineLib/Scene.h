#pragma once
#include "Object.h"

struct ICollision;
struct IQuadTree;
class Scene : public Object
{
public:
	void UseQuadTree();
	void AllCollisionUpdate();
	void CheckDeath();

	bool isUseQuadTree = false;
	IQuadTree* pQuad;
	std::vector<ICollision*> m_pCollisionList;
	std::vector<Object*> deathNote;
};

