#include "CBoxColider.h"
#include "COriBoxColider.h"
#include "CSphereColider.h"
#include <list>
#include <EngineLib/Transform.h>

void CSphereColider::SetTransform(Transform& _transform)
{
	m_Sphere->Center.x = _transform.worldPosition.x;
	m_Sphere->Center.y = _transform.worldPosition.y;
	m_Sphere->Center.z = _transform.worldPosition.z;

	m_Sphere->Radius = (_transform.worldScale.x > _transform.worldScale.y) ? _transform.worldScale.x : _transform.worldScale.y;
}

bool CSphereColider::Collision(IBoxColider* pCol)
{
	CBoxColider* pCast = (CBoxColider*)pCol;
	return m_Sphere->Intersects(*pCast->m_AABB);
}

bool CSphereColider::Collision(IOriBoxColider* pCol)
{
	COriBoxColider* pCast = (COriBoxColider*)pCol;
	return m_Sphere->Intersects(*pCast->m_OBB);
}

bool CSphereColider::Collision(ISphereColider* pCol)
{
	CSphereColider* pCast = (CSphereColider*)pCol;
	return m_Sphere->Intersects(*pCast->m_Sphere);
}