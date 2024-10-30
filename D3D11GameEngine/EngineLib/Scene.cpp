#include "Pre.h"
#include "Scene.h"
#include "Colider.h"

void Scene::AddCollision(Colider* pCol)
{
	dynamicColiders.push_back(pCol);
	if (pQuadRoot)
	{
		pQuadRoot->Insert(pCol);
	}
}

void Scene::UpdateQuadTree()
{
	pQuadRoot->Clear();
	for (Colider* pCol : dynamicColiders)
	{
		pQuadRoot->Insert(pCol);
	}
	pQuadRoot->CollisionList();
}

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

