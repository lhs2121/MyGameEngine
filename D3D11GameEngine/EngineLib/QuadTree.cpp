#include "Pre.h"
#include "QuadTree.h"

int CQuadTree::maxLevel = 0;

void CQuadTree::DivideToMaxLevel()
{
	if (level == maxLevel)
		return;

	if (pNode0)
		__debugbreak();


	pNode0 = CreateChild<CQuadTree>();
	pNode0->x = x + width / 4;
	pNode0->y = y + height / 4;
	pNode0->width = width / 2;
	pNode0->height = height / 2;
	pNode0->level = level + 1;
	pNode0->col = pNode0->CreateChild<Colider>();
	pNode0->transform.SetLocalPosition({pNode0->x, pNode0->y});
	pNode0->transform.SetLocalScale({ pNode0->width ,pNode0->height });
	pNode0->DivideToMaxLevel();

	pNode1 = CreateChild<CQuadTree>();
	pNode1->x = x - width / 4;
	pNode1->y = y + height / 4;
	pNode1->width = width / 2;
	pNode1->height = height / 2;
	pNode1->level = level + 1;
	pNode1->col = pNode1->CreateChild<Colider>();
	pNode1->transform.SetLocalPosition({ pNode1->x, pNode1->y });
	pNode1->transform.SetLocalScale({ pNode1->width ,pNode1->height });
	pNode1->DivideToMaxLevel();

	pNode2 = CreateChild<CQuadTree>();
	pNode2->x = x - width / 4;
	pNode2->y = y - height / 4;
	pNode2->width = width / 2;
	pNode2->height = height / 2;
	pNode2->level = level + 1;
	pNode2->col = pNode2->CreateChild<Colider>();
	pNode2->transform.SetLocalPosition({ pNode2->x, pNode2->y });
	pNode2->transform.SetLocalScale({ pNode2->width ,pNode2->height });
	pNode2->DivideToMaxLevel();

	pNode3 = CreateChild<CQuadTree>();
	pNode3->x = x + width / 4;
	pNode3->y = y - height / 4;
	pNode3->width = width / 2;
	pNode3->height = height / 2;
	pNode3->level = level + 1;
	pNode3->col = pNode3->CreateChild<Colider>();
	pNode3->transform.SetLocalPosition({ pNode3->x, pNode3->y });
	pNode3->transform.SetLocalScale({ pNode3->width ,pNode3->height });
	pNode3->DivideToMaxLevel();
}

void CQuadTree::Divide()
{
	if (pNode0)
		__debugbreak();

	pNode0 = new CQuadTree;
	pNode0->x = x + width / 4;
	pNode0->y = y + height / 4;
	pNode0->width = width / 2;
	pNode0->height = height / 2;
	pNode0->level = level + 1;

	pNode1 = new CQuadTree;
	pNode1->x = x - width / 4;
	pNode1->y = y + height / 4;
	pNode1->width = width / 2;
	pNode1->height = height / 2;
	pNode1->level = level + 1;

	pNode2 = new CQuadTree;
	pNode2->x = x - width / 4;
	pNode2->y = y - height / 4;
	pNode2->width = width / 2;
	pNode2->height = height / 2;
	pNode2->level = level + 1;

	pNode3 = new CQuadTree;
	pNode3->x = x + width / 4;
	pNode3->y = y - height / 4;
	pNode3->width = width / 2;
	pNode3->height = height / 2;
	pNode3->level = level + 1;
}
