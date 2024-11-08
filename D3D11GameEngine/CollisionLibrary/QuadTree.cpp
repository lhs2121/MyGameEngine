#include "pch.h"
#include "QuadTree.h"

int g_quadMaxlevel = 0;

CQuadTree::~CQuadTree()
{
	if(pNode != nullptr)
		delete pNode;
}
void CQuadTree::Initialize(float posX, float posY, float width, float height, int maxlevel)
{
	pNode = new CQuadNode;
	pNode->m_x = posX;
	pNode->m_y = posY;
	pNode->m_width = width;
	pNode->m_height = height;
	pNode->m_level = 1;

	CreateCollision(&pNode->m_pBoundaryCollision);
	g_quadMaxlevel = maxlevel;
	pNode->SplitToMaxLevel();
}

void CQuadTree::UpdateCollision(ICollision* pCol)
{

}

CQuadNode::~CQuadNode()
{
	if (m_pBoundaryCollision)
		DeleteCollision(m_pBoundaryCollision);

	for (size_t i = 0; i < 4; i++)
	{
		if (pChilds[i] != nullptr)
		{
			delete pChilds[i];
		}
	}
}

void CQuadNode::Split()
{
	if (pChilds[0] != nullptr)
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
		pChilds[i] = new CQuadNode;
		pChilds[i]->m_x = childPosX[i];
		pChilds[i]->m_y = childPosY[i];
		pChilds[i]->m_width = childWidth;
		pChilds[i]->m_height = childHeight;
		pChilds[i]->m_level = m_level + 1;
		CreateCollision(&pChilds[i]->m_pBoundaryCollision);
	}
}

void CQuadNode::SplitToMaxLevel()
{
	if (pChilds[0] != nullptr)
		__debugbreak();

	if (m_level == g_quadMaxlevel)
		return;
	
	Split();
	for (size_t i = 0; i < 4; i++)
	{
		pChilds[i]->SplitToMaxLevel();
	}
}

void CQuadNode::insert(ICollision* pCol)
{
	bool isCol = Collision(m_pBoundaryCollision, pCol);
	if (isCol == false)
		return;

	if (pChilds[0] == nullptr)
	{
		m_pCollisions.push_back(pCol);
		return;
	}

	for (size_t i = 0; i < 4; i++)
	{
		pChilds[i]->insert(pCol);
	}
}

bool AABB2D(float x, float y, float w, float h, float x2, float y2, float w2, float h2)
{
	float x1_right = x + w;
	float y1_bottom = y + h;

	float x2_right = x2 + w2;
	float y2_bottom = y2 + h2;

	if (x < x2_right && x1_right > x2 && y < y2_bottom && y1_bottom > y2) 
	{
		return true; 
	}
	return false;
}