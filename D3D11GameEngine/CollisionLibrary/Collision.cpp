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

void CCollision::UpdateTransform(FXMVECTOR scale, FXMVECTOR rot, FXMVECTOR pos)
{
	switch (m_type)
	{
	case AABB:
	{
		BoundingBox* shape = (BoundingBox*)m_pShape;
		XMStoreFloat3(&shape->Center, pos);
		XMStoreFloat3(&shape->Extents, scale);
		break;
	}
	case SPHERE:
	{
		BoundingSphere* shape2 = (BoundingSphere*)m_pShape;
		XMStoreFloat3(&shape2->Center, pos);
		XMStoreFloat(&shape2->Radius, scale);
		break;
	}
	case OBB:
	{
		BoundingOrientedBox* shape3 = (BoundingOrientedBox*)m_pShape;
		XMStoreFloat3(&shape3->Center, pos);
		XMStoreFloat3(&shape3->Extents, scale);
		XMStoreFloat4(&shape3->Orientation, rot);
		break;
	}
	default:
		break;
	}
}




