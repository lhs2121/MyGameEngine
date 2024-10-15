#include "Pre.h"
#include "QuadTree.h"
#include "Scene.h"
#include <DirectXCollision.h>

int CQuadTree::maxLevel = 1;

void CQuadTree::DivideToMaxLevel()
{
	if (level > maxLevel)
		return;
	

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
		CQuadTree* newQuadTree = CreateChild<CQuadTree>();
		newQuadTree->x = childPosition[i].x;
		newQuadTree->y = childPosition[i].y;
		newQuadTree->width = childWidth;
		newQuadTree->height = childHeight;
		newQuadTree->level = level + 1;

		if (level == maxLevel)
		{
			GetScene()->quTails.push_back(newQuadTree);
			newQuadTree->transform.SetLocalPosition({ childPosition[i].x, childPosition[i].y });
			newQuadTree->transform.SetLocalScale({ childWidth , childHeight });
			newQuadTree->pCol = newQuadTree->CreateChild<Colider>();
		}
		newQuadTree->pParent = this;
		newQuadTree->DivideToMaxLevel();

		pNode[i] = newQuadTree;
	}
}

void CQuadTree::Divide()
{
	if (pNode[0])
		__debugbreak();

	pCol->Destroy();
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

		pNode[i]->pCol = pNode[i]->CreateChild<Colider>();
		pNode[i]->transform.SetLocalPosition({ childPosition[i].x, childPosition[i].y });
		pNode[i]->transform.SetLocalScale({ 0.5f , 0.5f });
		pNode[i]->pCol->Disenable();
		pNode[i]->pParent = this;
	}
}

void CQuadTree::UpdateList(Colider* pOther)
{
	if (pCol->Collision(pOther))
	{
		ColiderList.push_back(pOther);
	}
}

void CQuadTree::CollisionList()
{
	if (pNode[0])
		__debugbreak();

	size_t size = ColiderList.size();
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = i + 1; j < size; j++)
		{
			Colider* left = ColiderList[i];
			Colider* right = ColiderList[j];
			left->Collision(right);
		}
	}
}