#include "pch.h"
#include "ICollision.h"
#include "Collision.h"
#include "Collision2D.h"

void CreateCollision(ICollision** ppCol)
{
	*ppCol = new CCollision;
}

bool Collision(ICollision* pLeft, ICollision* pRight)
{
	CCollision* pCastLeft = (CCollision*)pLeft;
	CCollision* pCastRight = (CCollision*)pRight;

	COLLISION_TYPE type1 = pCastLeft->GetType();
	COLLISION_TYPE type2 = pCastRight->GetType();

	if (type2 < type1)
	{
		CCollision* pTemp = pCastLeft;
		pCastLeft = pCastRight;
		pCastRight = pTemp;
	}

	int combine = type1 | type2;
	void* pShape1 = pCastLeft->Get3DShape();
	void* pShape2 = pCastRight->Get3DShape();

	//2d¶û 3dÀÇ Ãæµ¹Àº false
	if (pShape1 != nullptr && pShape2 == nullptr)
		return false;
	if (pShape1 == nullptr && pShape2 != nullptr)
		return false;

	switch (combine)
	{
	case COLLISION_TYPE::AABB2D | COLLISION_TYPE::AABB2D:
		return AABB2DvsAABB2D(pCastLeft, pCastRight);
	case COLLISION_TYPE::AABB2D | COLLISION_TYPE::SPHERE2D:
		return AABB2DvsSPHERE2D(pCastLeft, pCastRight);
	case COLLISION_TYPE::AABB2D | COLLISION_TYPE::OBB2D:
		return AABB2DvsOBB2D(pCastLeft, pCastRight);
	case COLLISION_TYPE::SPHERE2D | COLLISION_TYPE::SPHERE2D:
		return SPHERE2DvsSPHERE2D(pCastLeft, pCastRight);
	case COLLISION_TYPE::SPHERE2D | COLLISION_TYPE::OBB2D:
		return SPHERE2DvsOBB2D(pCastLeft, pCastRight);
	case COLLISION_TYPE::OBB2D | COLLISION_TYPE::OBB2D:
		return OBB2DvsOBB2D(pCastLeft, pCastRight);
	case COLLISION_TYPE::AABB3D | COLLISION_TYPE::AABB3D:
		return ((DirectX::BoundingBox*)pShape1)->Intersects(*((DirectX::BoundingBox*)pShape2));
	case COLLISION_TYPE::AABB3D | COLLISION_TYPE::SPHERE3D:
		return ((DirectX::BoundingBox*)pShape1)->Intersects(*((DirectX::BoundingSphere*)pShape2));
	case COLLISION_TYPE::AABB3D | COLLISION_TYPE::OBB3D:
		return ((DirectX::BoundingBox*)pShape1)->Intersects(*((DirectX::BoundingOrientedBox*)pShape2));
	case COLLISION_TYPE::SPHERE3D | COLLISION_TYPE::SPHERE3D:
		return ((DirectX::BoundingSphere*)pShape1)->Intersects(*((DirectX::BoundingSphere*)pShape2));
	case COLLISION_TYPE::SPHERE3D | COLLISION_TYPE::OBB3D:
		return ((DirectX::BoundingSphere*)pShape1)->Intersects(*((DirectX::BoundingOrientedBox*)pShape2));
	case COLLISION_TYPE::OBB3D | COLLISION_TYPE::OBB3D:
		return ((DirectX::BoundingOrientedBox*)pShape1)->Intersects(*((DirectX::BoundingOrientedBox*)pShape2));
	default:
		break;
	}
}
