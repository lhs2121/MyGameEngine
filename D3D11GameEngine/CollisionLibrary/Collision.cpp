#include "pch.h"
#include "Collision.h"

CCollision::CCollision()
{
	m_pShape = new DirectX::BoundingBox;
}

CCollision::~CCollision()
{
	if (m_pShape != nullptr)
	{
		delete m_pShape;
		m_pShape = nullptr;
	}
}

void CCollision::SetType(COLLISION_TYPE type)
{
	if (m_type == type)
		return;

	m_type = type;
	if (m_pShape != nullptr)
	{
		delete m_pShape;
		m_pShape = nullptr;
	}

	switch (m_type)
	{
	case AABB:
		m_pShape = new BoundingBox;
		break;
	case SPHERE:
		m_pShape = new BoundingSphere;
		break;
	case OBB:
		m_pShape = new BoundingOrientedBox;
		break;
	default:
		break;
	}
}

void CCollision::UpdateTransform(Transform* pTransform)
{
	XMVECTOR& position = pTransform->vecWorldPosition;
	XMVECTOR& scale = pTransform->vecWorldScale;
	XMVECTOR& rotation = pTransform->vecWorldRotation;

	switch (m_type)
	{
	case AABB:
	{
		BoundingBox* shape = (BoundingBox*)m_pShape;
		XMStoreFloat3(&shape->Center, position);
		XMStoreFloat3(&shape->Extents, scale);
		break;
	}
	case SPHERE:
	{
		BoundingSphere* shape2 = (BoundingSphere*)m_pShape;
		XMStoreFloat3(&shape2->Center, position);
		XMStoreFloat(&shape2->Radius, scale);
		break;
	}
	case OBB:
	{
		BoundingOrientedBox* shape3 = (BoundingOrientedBox*)m_pShape;
		XMStoreFloat3(&shape3->Center, position);
		XMStoreFloat3(&shape3->Extents, scale);
		XMStoreFloat4(&shape3->Orientation, rotation);
		break;
	}
	default:
		break;
	}
}

void CCollision::UpdateTransform(XMVECTOR& vecPos, XMVECTOR& vecScale, XMVECTOR& vecRot)
{

	switch (m_type)
	{
	case AABB:
	{
		BoundingBox* shape = (BoundingBox*)m_pShape;
		XMStoreFloat3(&shape->Center, vecPos);
		XMStoreFloat3(&shape->Extents, vecScale);
		break;
	}
	case SPHERE:
	{
		BoundingSphere* shape2 = (BoundingSphere*)m_pShape;
		XMStoreFloat3(&shape2->Center, vecPos);
		XMStoreFloat(&shape2->Radius, vecScale);
		break;
	}
	case OBB:
	{
		BoundingOrientedBox* shape3 = (BoundingOrientedBox*)m_pShape;
		XMStoreFloat3(&shape3->Center, vecPos);
		XMStoreFloat3(&shape3->Extents, vecScale);
		XMStoreFloat4(&shape3->Orientation, vecRot);
		break;
	}
	default:
		break;
	}
}


