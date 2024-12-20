#include "pch.h"
#include "Scene.h"

Scene::~Scene()
{
	if (pQuad)
	{
		DeleteQuadTree(pQuad);
	}

	for (ICollision* pCol : m_pCollisionList)
	{
		DeleteCollision(pCol);
	}
}

void Scene::UseQuadTree()
{
	if (isUseQuadTree)
		return;

	CreateQuadTree(&pQuad);
	pQuad->Initialize(0, 0, 500, 500, 4, m_pRenderer);

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

	pQuad->DebugRender();
}

void Scene::CheckDeath()
{
	for (Object* object: deathNote)
	{
		object->Getm_pParent()->RemoveChild(object);
		object->AllRelease();
		delete object;
	}
	deathNote.clear();
}



