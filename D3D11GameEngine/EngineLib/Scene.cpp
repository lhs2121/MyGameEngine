#include "Pre.h"
#include "Scene.h"

void Scene::CheckDeath()
{
	for (Object* object: deathNote)
	{
		object->GetParent()->RemoveChild(object);
		object->AllRelease();
		delete object;
	}
	deathNote.clear();
}

void Scene::AddCollision(ICollision* pCol)
{
	m_collisionList.push_back(pCol);
}

