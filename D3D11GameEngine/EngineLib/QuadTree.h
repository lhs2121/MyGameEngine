#pragma once
#include "Colider.h"

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

	static int maxLevel;
	int level = 0;

	float x;
	float y;
	float width;
	float height;

	Colider* col = nullptr;
	CQuadTree* pNode0 = nullptr;
	CQuadTree* pNode1 = nullptr;
	CQuadTree* pNode2 = nullptr;
	CQuadTree* pNode3 = nullptr;
};