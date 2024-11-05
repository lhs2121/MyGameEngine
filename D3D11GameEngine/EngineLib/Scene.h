#pragma once
#include "Object.h"

struct ICollision;
class Scene : public Object
{
public:
	void CheckDeath();
	void AddCollision(ICollision* pCol);
	
	std::vector<ICollision*> m_collisionList;
	std::vector<Object*> deathNote;
};

