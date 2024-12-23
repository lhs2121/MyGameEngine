#pragma once
#include "Object.h"

struct ICollision;
struct IQuadTree;
class Scene : public Object
{
public:
	~Scene();
	void UseQuadTree();
	void AllCollisionUpdate();
	void CheckDeath();

	bool m_bUseQuadtree = false;
	IQuadTree* m_pQuad = nullptr;
	std::vector<ICollision*> m_pCollisionList;
	std::vector<Object*> m_pDeathObjectList;
};

