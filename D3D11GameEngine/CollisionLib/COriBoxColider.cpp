#include "CBoxColider.h"
#include "COriBoxColider.h"
#include "CSphereColider.h"
#include <list>
#include <EngineLib/Transform.h>

void COriBoxColider::SetTransform(Transform& _transform)
{
	m_OBB->Center.x = _transform.worldPosition.x;
	m_OBB->Center.y = _transform.worldPosition.y;
	m_OBB->Center.z = _transform.worldPosition.z;

	m_OBB->Extents.x = _transform.worldScale.x;
	m_OBB->Extents.y = _transform.worldScale.x;
	m_OBB->Extents.z = _transform.worldScale.x;

	m_OBB->Orientation.x = _transform.worldRotation.x;
	m_OBB->Orientation.y = _transform.worldRotation.y;
	m_OBB->Orientation.z = _transform.worldRotation.z;
}

bool COriBoxColider::Collision(IBoxColider* pCol)
{
	CBoxColider* pCast = (CBoxColider*)pCol;
	return m_OBB->Intersects(*pCast->m_AABB);
}

bool COriBoxColider::Collision(IOriBoxColider* pCol)
{
	COriBoxColider* pCast = (COriBoxColider*)pCol;
	return m_OBB->Intersects(*pCast->m_OBB);
}

bool COriBoxColider::Collision(ISphereColider* pCol)
{
	CSphereColider* pCast = (CSphereColider*)pCol;
	return m_OBB->Intersects(*pCast->m_Sphere);
}