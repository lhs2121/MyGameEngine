#include "CBoxColider.h"
#include "COriBoxColider.h"
#include "CSphereColider.h"
#include <list>
#include <EngineLib/Transform.h>

void CBoxColider::SetTransform(Transform& _transform)
{
	m_AABB->Center.x = _transform.worldPosition.x;
	m_AABB->Center.y = _transform.worldPosition.y;
	m_AABB->Center.z = _transform.worldPosition.z;

	m_AABB->Extents.x = _transform.worldScale.x;
	m_AABB->Extents.y = _transform.worldScale.x;
	m_AABB->Extents.z = _transform.worldScale.x;
}

bool CBoxColider::Collision(IBoxColider* pCol)
{
	CBoxColider* pCast = (CBoxColider*)pCol;
	return m_AABB->Intersects(*pCast->m_AABB);
}

bool CBoxColider::Collision(IOriBoxColider* pCol)
{
	COriBoxColider* pCast = (COriBoxColider*)pCol;
	return m_AABB->Intersects(*pCast->m_OBB);
}

bool CBoxColider::Collision(ISphereColider* pCol)
{
	CSphereColider* pCast = (CSphereColider*)pCol;
	return m_AABB->Intersects(*pCast->m_Sphere);
}
