#include "Pre.h"
#include "Scene.h"

void Scene::UseQuadTree()
{
	if (isUseQuadTree)
		return;

	CreateQuadTree(&pQuad);
	pQuad->Initialize(0, 0, 1366, 789, 2);

	isUseQuadTree = true;
}

void Scene::AllCollisionUpdate()
{
	if (isUseQuadTree)
	{
		pQuad->Clear();
		for (ICollision* pCol : m_pCollisionList)
		{
			pQuad->Insert(pCol);
		}
	}
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



