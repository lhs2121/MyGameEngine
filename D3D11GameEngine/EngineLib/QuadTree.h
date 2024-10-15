#pragma once
#include "Colider.h"
#include "CollisionList.h"

class CQuadTree : public Object
{
public:
	void Init(float _x, float _y, float _width, float _height,int _maxLevel)
	{
		if (level != 0)
			__debugbreak();

		x = _x;
		y = _y;
		width = _width;
		height = _height;
		maxLevel = _maxLevel;
	}
	void DivideToMaxLevel();
	void Divide();
	void CollisionAll();
	void Collision();

	static int maxLevel;
	int level = 0;

	float x;
	float y;
	float width;
	float height;

	Colider* col = nullptr;
	CQuadTree* pParent = nullptr;

	CQuadTree* pNode[4];
	CCollisionList* Group;
};