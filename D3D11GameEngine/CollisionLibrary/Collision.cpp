#include "pch.h"
#include "Collision.h"

CCollision::~CCollision()
{
}

void CCollision::SetType(COLLISION_TYPE type)
{
	if (type != m_type && m_3dShape != nullptr)
	{
		delete m_3dShape;
		m_3dShape = nullptr;
	}

	m_type = type;
	switch (m_type)
	{
	case AABB3D:
		m_3dShape = new DirectX::BoundingBox;
		break;
	case SPHERE3D:
		m_3dShape = new DirectX::BoundingSphere;
		break;
	case OBB3D:
		m_3dShape = new DirectX::BoundingOrientedBox;
		break;
	default:
		break;
	}
}

void CCollision::UpdateCollision(float x, float y, float width, float height)
{
	m_x = x;
	m_y = y;    
	m_width = width;
	m_height = height;
}
