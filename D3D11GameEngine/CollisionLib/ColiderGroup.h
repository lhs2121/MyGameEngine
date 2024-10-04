#pragma once
#include "CollisionAPI.h"

class ColiderGroup : public IColiderGroup
{
public:
	virtual void AddCollision() = 0;
	virtual void Collision(IColiderGroup* pColGroup) = 0;
};