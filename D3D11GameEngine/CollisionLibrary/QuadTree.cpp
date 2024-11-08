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

	g_quadMaxlevel = maxlevel;
	pNode->SplitToMaxLevel();
}

void CQuadTree::UpdateCollision(ICollision* pCol)
{

}

CQuadNode::~CQuadNode()
{
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
	}
}

void CQuadNode::SplitToMaxLevel()
{
	if (pChilds[0] != nullptr)
		__debugbreak();

	if (m_level == g_quadMaxlevel)
		return;
	
	for (size_t i = 0; i < 4; i++)
	{
		pChilds[i]->Split();
		pChilds[i]->SplitToMaxLevel();
	}
}
