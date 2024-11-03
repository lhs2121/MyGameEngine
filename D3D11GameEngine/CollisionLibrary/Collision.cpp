#include "pch.h"
#include "Collision.h"

CCollision::CCollision()
{
	m_3dShape = new DirectX::BoundingBox;
}

CCollision::~CCollision()
{
	if (m_3dShape != nullptr)
	{
		delete m_3dShape;
		m_3dShape = nullptr;
	}
}

void CCollision::SetType(COLLISION_TYPE type)
{
	if (m_type == type)
		return;

	m_type = type;
	if (m_3dShape != nullptr)
	{
		delete m_3dShape;
		m_3dShape = nullptr;
	}

	switch (m_type)
	{
	case AABB:
		m_3dShape = new BoundingBox;
		break;
	case SPHERE:
		m_3dShape = new BoundingSphere;
		break;
	case OBB:
		m_3dShape = new BoundingOrientedBox;
		break;
	default:
		break;
	}
}

void CCollision::UpdateTransform(XMVECTOR& position, XMVECTOR& scale, XMVECTOR& rotation)
{
	switch (m_type)
	{
	case AABB:
	{
		BoundingBox* shape = (BoundingBox*)m_3dShape;
		XMStoreFloat3(&shape->Center, position);
		XMStoreFloat3(&shape->Extents, scale);
		break;
	}
	case SPHERE:
	{
		BoundingSphere* shape2 = (BoundingSphere*)m_3dShape;
		XMStoreFloat3(&shape2->Center, position);
		XMStoreFloat(&shape2->Radius, scale);
		break;
	}
	case OBB:
	{
		BoundingOrientedBox* shape3 = (BoundingOrientedBox*)m_3dShape;
		XMStoreFloat3(&shape3->Center, position);
		XMStoreFloat3(&shape3->Extents, scale);
		XMStoreFloat4(&shape3->Orientation, rotation);
		break;
	}
	default:
		break;
	}
}


