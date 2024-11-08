#pragma once
#include "ICollision.h"

class CQuadTree : public IQuadTree
{
private:
	void UpdateCollision(ICollision* pCol) override;
public:
	~CQuadTree();
};