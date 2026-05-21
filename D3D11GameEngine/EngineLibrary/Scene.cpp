#include "pch.h"
#include "Scene.h"

void Scene::CheckDeath()
{
	for (Object* object: m_pDeathObjectList)
	{
		object->GetParent()->RemoveChild(object);
		object->AllRelease();
		delete object;
	}
	m_pDeathObjectList.clear();
}



