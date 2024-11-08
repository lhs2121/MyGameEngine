#pragma once
#include "ICollision.h"
#include <vector>

struct CQuadNode
{
	~CQuadNode();
	float m_x;
	float m_y;
	float m_width;
	float m_height;
	int m_level;

	void Split();
	void SplitToMaxLevel();
	CQuadNode* pChilds[4] = { nullptr };
	std::vector<ICollision*> m_pCollisions;
};
class CQuadTree : public IQuadTree
{
private:
	void Initialize(float posX, float posY, float width, float height, int maxlevel) override;
	void UpdateCollision(ICollision* pCol) override;

	CQuadNode* pNode = nullptr;
public:
	~CQuadTree();
};