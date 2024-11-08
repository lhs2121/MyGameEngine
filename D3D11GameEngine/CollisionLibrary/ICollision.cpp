#include "pch.h"
#include "ICollision.h"
#include "Collision.h"
#include "Collision2D.h"
#include "QuadTree.h"

void CreateQuadTree(IQuadTree** ppQuad)
{
	*ppQuad = new CQuadTree;
}

void DeleteQuadTree(IQuadTree* pQuad)
{
	delete ((CQuadTree*)pQuad);
}

void CreateCollision(ICollision** ppCol)
{
	*ppCol = new CCollision;
}

void DeleteCollision(ICollision* pCol)
{
	CCollision* pCastCol = (CCollision*)pCol;
	delete pCastCol;
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

	switch (combine)
	{
	case COLLISION_TYPE::AABB | COLLISION_TYPE::AABB:
		return ((DirectX::BoundingBox*)pShape1)->Intersects(*((DirectX::BoundingBox*)pShape2));
	case COLLISION_TYPE::AABB | COLLISION_TYPE::SPHERE:
		return ((DirectX::BoundingBox*)pShape1)->Intersects(*((DirectX::BoundingSphere*)pShape2));
	case COLLISION_TYPE::AABB | COLLISION_TYPE::OBB:
		return ((DirectX::BoundingBox*)pShape1)->Intersects(*((DirectX::BoundingOrientedBox*)pShape2));
	case COLLISION_TYPE::SPHERE | COLLISION_TYPE::SPHERE:
		return ((DirectX::BoundingSphere*)pShape1)->Intersects(*((DirectX::BoundingSphere*)pShape2));
	case COLLISION_TYPE::SPHERE | COLLISION_TYPE::OBB:
		return ((DirectX::BoundingSphere*)pShape1)->Intersects(*((DirectX::BoundingOrientedBox*)pShape2));
	case COLLISION_TYPE::OBB | COLLISION_TYPE::OBB:
		return ((DirectX::BoundingOrientedBox*)pShape1)->Intersects(*((DirectX::BoundingOrientedBox*)pShape2));
	default:
		return false;
	}
}
