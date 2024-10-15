#pragma once
#include "Colider.h"

class CQuadTree : public Object
{
public:
	void Init(float _x, float _y, float _width, float _height,int _maxLevel)
	{
		if (level != 1)
			__debugbreak();

		x = _x;
		y = _y;
		width = _width;
		height = _height;
		maxLevel = _maxLevel;
	}
	void DivideToMaxLevel();
	void Divide();
	void UpdateList(Colider* pOther);
	void CollisionList();
	static int maxLevel;
	int level = 1;

	float x;
	float y;
	float width;
	float height;

	Colider* pCol = nullptr;
	std::vector<Colider*> ColiderList;
	CQuadTree* pParent = nullptr;
	CQuadTree* pNode[4];
};