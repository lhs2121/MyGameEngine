#pragma once
#include "Object.h"

class Scene : public Object
{
public:
	void CheckDeath();

	std::vector<Object*> m_pDeathObjectList;
};

