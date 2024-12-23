#include "pch.h"
#include "Scene.h"

Scene::~Scene()
{
	if (m_bUseQuadtree)
	{
		DeleteQuadTree(m_pQuad);
	}

	for (ICollision* pCol : m_pCollisionList)
	{
		DeleteCollision(pCol);
	}
}

void Scene::UseQuadTree()
{
	if (m_bUseQuadtree)
		return;

	CreateQuadTree(&m_pQuad);
	m_pQuad->Initialize(0, 0, 500, 500, 4, m_pRenderer);

	m_bUseQuadtree = true;
}

void Scene::AllCollisionUpdate()
{
	if (m_bUseQuadtree)
	{
		m_pQuad->Clear();
		for (ICollision* pCol : m_pCollisionList)
		{
			m_pQuad->Insert(pCol);
		}
	}

	m_pQuad->DebugRender();
}

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



