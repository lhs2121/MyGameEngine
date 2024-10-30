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

	float2 chPos[] =
	{
		{x + width / 4, y + height / 4},
		{x - width / 4, y + height / 4},
		{x - width / 4, y - height / 4},
		{x + width / 4, y - height / 4}
	};
	float chWidth = width / 2;
	float chHeight = height / 2;

	for (size_t i = 0; i < 4; i++)
	{
		CQuadTree* pNewQuad = CreateChild<CQuadTree>();
		pNewQuad->x = chPos[i].x;
		pNewQuad->y = chPos[i].y;
		pNewQuad->width = chWidth;
		pNewQuad->height = chHeight;
		pNewQuad->level = level + 1;
		pNewQuad->pParent = this;

		pNewQuad->pCol = pNewQuad->CreateChild<Colider>();
		pNewQuad->transform.SetLocalPosition({ chPos[i].x, chPos[i].y });
		pNewQuad->transform.SetLocalScale({ 0.5f , 0.5f });

		pNewQuad->DivideToMaxLevel();
		pNode[i] = pNewQuad;
	}
}

void CQuadTree::Divide()
{
	if (pNode[0])
		__debugbreak();

	pCol->Destroy();
	float2 chPos[] =
	{
		{width / 4, height / 4},
		{-width / 4, height / 4},
		{-width / 4, -height / 4},
		{width / 4, -height / 4}
	};
	float chWidth = width / 2;
	float chHeight = height / 2;
	       
	for (size_t i = 0; i < 4; i++)
	{
		pNode[i] = CreateChild<CQuadTree>();
		pNode[i]->x = chPos[i].x;
		pNode[i]->y = chPos[i].y;
		pNode[i]->width = chWidth;
		pNode[i]->height = chHeight;
		pNode[i]->level = level + 1;

		pNode[i]->pCol = pNode[i]->CreateChild<Colider>();
		pNode[i]->transform.SetLocalPosition({ chPos[i].x, chPos[i].y });
		pNode[i]->transform.SetLocalScale({ 0.5f , 0.5f });
		pNode[i]->pParent = this;
	}
}

void CQuadTree::Clear()
{
	if (pNode[0] == nullptr)
	{
		ColiderList.clear();
		return;
	}

	for (size_t i = 0; i < 4; i++)
	{
		pNode[i]->Clear();
	}
}

void CQuadTree::Insert(Colider* pOther)
{
	if (!pCol->SimpleCollision(pOther))
		return;

	if (pNode[0] == nullptr)
	{
		ColiderList.push_back(pOther);
		return;
	}

	for (size_t i = 0; i < 4; i++)
	{
		pNode[i]->Insert(pOther);
	}
}

void CQuadTree::CollisionList()
{
	if (pNode[0] != nullptr)
	{
		for (size_t i = 0; i < 4; i++)
		{
			pNode[i]->CollisionList();
		}
		return;
	}

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