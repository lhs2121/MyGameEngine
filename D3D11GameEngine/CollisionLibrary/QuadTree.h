#pragma once
#include "ICollision.h"
#include <vector>

struct CQuadNode
{
	~CQuadNode();
	void Split();
	void SplitToMaxLevel();
	void insert(ICollision* pCol);

	float m_x;
	float m_y;
	float m_width;
	float m_height;
	int m_level;

	CQuadNode* pChilds[4] = { 0 };
	std::vector<ICollision*> m_pCollisions;
};
class CQuadTree : public IQuadTree
{
private:
	void Initialize(float posX, float posY, float width, float height, int maxlevel) override;
	void Insert(ICollision* pCol) override;

	CQuadNode* pNode = nullptr;
public:
	~CQuadTree();
};

bool AABB2D(CQuadNode* pNode, ICollision* pCol);