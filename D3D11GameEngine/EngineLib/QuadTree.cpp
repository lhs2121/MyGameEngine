#include "Pre.h"
#include "QuadTree.h"

int CQuadTree::maxLevel = 0;

void CQuadTree::DivideToMaxLevel()
{
	if (level > maxLevel)
	{
		return;
	}

	if (pNode[0])
		__debugbreak();

	float2 childPosition[] =
	{
		{x + width / 4, y + height / 4},
		{x - width / 4, y + height / 4},
		{x - width / 4, y - height / 4},
		{x + width / 4, y - height / 4}
	};
	float childWidth = width / 2;
	float childHeight = height / 2;

	for (size_t i = 0; i < 4; i++)
	{
		pNode[i] = CreateChild<CQuadTree>();
		pNode[i]->x = childPosition[i].x;
		pNode[i]->y = childPosition[i].y;
		pNode[i]->width = childWidth;
		pNode[i]->height = childHeight;
		pNode[i]->level = level + 1;

		if (level == maxLevel)
		{
			pNode[i]->transform.SetLocalPosition({ childPosition[i].x, childPosition[i].y });
			pNode[i]->transform.SetLocalScale({ childWidth , childHeight });
			pNode[i]->col = pNode[i]->CreateChild<Colider>();
		}
		pNode[i]->pParent = this;
		pNode[i]->DivideToMaxLevel();
	}
}

void CQuadTree::Divide()
{
	if (pNode[0])
		__debugbreak();

	col->SetDeath();
	float2 childPosition[] =
	{
		{width / 4, height / 4},
		{-width / 4, height / 4},
		{-width / 4, -height / 4},
		{width / 4, -height / 4}
	};
	float childWidth = width / 2;
	float childHeight = height / 2;
	       
	for (size_t i = 0; i < 4; i++)
	{
		pNode[i] = CreateChild<CQuadTree>();
		pNode[i]->x = childPosition[i].x;
		pNode[i]->y = childPosition[i].y;
		pNode[i]->width = childWidth;
		pNode[i]->height = childHeight;
		pNode[i]->level = level + 1;
		pNode[i]->col = pNode[i]->CreateChild<Colider>();
		pNode[i]->transform.SetLocalPosition({ childPosition[i].x, childPosition[i].y });
		pNode[i]->transform.SetLocalScale({ 0.5f , 0.5f });
		pNode[i]->pParent = this;
	}
}
