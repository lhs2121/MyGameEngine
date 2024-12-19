#pragma once
#include "Interface.h"
#include <vector>

struct CQuadNode
{
	~CQuadNode();
	void Split();
	void SplitToMaxLevel();
	void Clear();
	void insert(ICollision* pCol);
	void DebugRender();

	float m_x;
	float m_y;
	float m_width;
	float m_height;
	int m_level;

	IRenderer* m_pRenderer = nullptr;
	CQuadNode* m_pChilds[4] = { 0 };
	std::vector<ICollision*> m_pCollisions;
};

class CQuadTree : public IQuadTree
{
private:
	void Initialize(float posX, float posY, float width, float height, int maxlevel, IRenderer* pRenderer) override;
    void Clear() override;
	void Insert(ICollision* pCol) override;
	void DebugRender() override;

	CQuadNode* pNode = nullptr;
public:
	~CQuadTree();
};

bool AABB2D(CQuadNode* pNode, ICollision* pCol);

extern std::vector<CQuadNode*> g_pDebugGreens;
extern std::vector<CQuadNode*> g_pDebugReds;