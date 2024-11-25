#include "pch.h"
#include "QuadTree.h"
#include "Collision.h"

int g_quadMaxlevel = 0;

CQuadTree::~CQuadTree()
{
	if (pNode != nullptr)
		delete pNode;
}
void CQuadTree::Initialize(float posX, float posY, float width, float height, int maxlevel, IRenderer* pRenderer)
{
	pNode = new CQuadNode;
	pNode->m_x = posX;
	pNode->m_y = posY;
	pNode->m_width = width;
	pNode->m_height = height;
	pNode->m_level = 1;
	pNode->m_pRenderer = pRenderer;

	g_quadMaxlevel = maxlevel;
	pNode->SplitToMaxLevel();
}

void CQuadTree::Clear()
{
	pNode->Clear();
}

void CQuadTree::Insert(ICollision* pCol)
{
	pNode->insert(pCol);
}

CQuadNode::~CQuadNode()
{
	for (size_t i = 0; i < 4; i++)
	{
		if (m_pChilds[i] != nullptr)
		{
			delete m_pChilds[i];
		}
	}
}

void CQuadNode::Split()
{
	if (m_pChilds[0] != nullptr)
		__debugbreak();

	float childPosX[4] =
	{
		m_x + m_width / 4,
		m_x - m_width / 4,
		m_x - m_width / 4,
		m_x + m_width / 4,
	};
	float childPosY[4] =
	{
		m_y + m_height / 4,
		m_y + m_height / 4,
		m_y - m_height / 4,
		m_y - m_height / 4,
	};

	float childWidth = m_width / 2;
	float childHeight = m_height / 2;
	for (size_t i = 0; i < 4; i++)
	{
		CQuadNode* pNode = new CQuadNode;
		pNode->m_pRenderer = m_pRenderer;
		pNode->m_x = childPosX[i];
		pNode->m_y = childPosY[i];
		pNode->m_width = childWidth;
		pNode->m_height = childHeight;
		pNode->m_level = m_level + 1;

		m_pChilds[i] = pNode;
	}
}

void CQuadNode::SplitToMaxLevel()
{
	if (m_pChilds[0] != nullptr)
		__debugbreak();

	if (m_level == g_quadMaxlevel)
		return;

	Split();
	for (size_t i = 0; i < 4; i++)
	{
		m_pChilds[i]->SplitToMaxLevel();
	}
}

void CQuadNode::Clear()
{
	m_pCollisions.clear();
	if (nullptr == m_pChilds[0])
		return;

	for (size_t i = 0; i < 4; i++)
	{
		m_pChilds[i]->Clear();
	}
}

void CQuadNode::insert(ICollision* pCol)
{
	bool isCol = AABB2D(this, pCol);
	if (isCol == false)
	{
		m_pRenderer->DrawRect2(m_x, m_y, m_width, m_height, { 1,0,0,1 });
		return;
	}

	if (m_pChilds[0] == nullptr)
	{
		m_pCollisions.push_back(pCol);
		m_pRenderer->DrawRect2(m_x, m_y, m_width, m_height, { 0,1,0,1 });
		return;
	}

	for (size_t i = 0; i < 4; i++)
	{
		m_pChilds[i]->insert(pCol);
	}
}

bool AABB2D(CQuadNode* pNode, ICollision* pCol)
{
	float x1 = pNode->m_x;
	float y1 = pNode->m_y;
	float w1 = pNode->m_width;
	float h1 = pNode->m_height;

	CCollision* pCast = (CCollision*)pCol;
	BoundingBox* aabb = (BoundingBox*)pCast->GetShape();

	float x2 = aabb->Center.x;
	float y2 = aabb->Center.y;
	float w2 = aabb->Extents.x;
	float h2 = aabb->Extents.y;

	float x1_left = x1 - w1 / 2;
	float x1_right = x1 + w1 / 2;
	float y1_top = y1 + h1 / 2;
	float y1_bottom = y1 - h1 / 2;

	float x2_left = x2 - w2 / 2;
	float x2_right = x2 + w2 / 2;
	float y2_top = y2 + h2 / 2;
	float y2_bottom = y2 - h2 / 2;

	if (x1_left < x2_right && x1_right > x2_left && y1_top > y2_bottom && y1_bottom < y2_top)
	{
		return true;
	}
	return false;
}
