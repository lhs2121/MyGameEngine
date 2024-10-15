#include "Pre.h"
#include "CollisionList.h"
#include <DirectXCollision.h> 

void CCollisionList::Collision()
{
	int size = ColiderList.size();
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = i+1; j < size; j++)
		{
			Colider* left = ColiderList[i];
			Colider* right = ColiderList[j];

			bool isCol = false;
			int leftType = left->collisionType;
			int rightType = right->collisionType;
			int combinedType = leftType | rightType;

			switch (combinedType)
			{
			case CollisionType::_AABB | CollisionType::_AABB:
				isCol = AABBvsAABB((AABB*)left->shape, (AABB*)right->shape);
				break;
			case CollisionType::_SPHERE | CollisionType::_SPHERE:
				isCol = SPHEREvsSPHERE((SPHERE*)left->shape, (SPHERE*)right->shape);
				break;
			case CollisionType::_OBB | CollisionType::_OBB:
				isCol = OBBvsOBB((OBB*)left->shape, (OBB*)right->shape);
				break;
			case CollisionType::_AABB | CollisionType::_SPHERE:
			{
				if (leftType == CollisionType::_AABB)
					isCol = AABBvsSPHERE((AABB*)left->shape, (SPHERE*)right->shape);
				else
					isCol = AABBvsSPHERE((AABB*)right->shape, (SPHERE*)left->shape);
				break;
			}
			case CollisionType::_AABB | CollisionType::_OBB:
			{
				if (leftType == CollisionType::_AABB)
					isCol = AABBvsOBB((AABB*)left->shape, (OBB*)right->shape);
				else
					isCol = AABBvsOBB((AABB*)right->shape, (OBB*)left->shape);
				break;
			}
			case CollisionType::_OBB | CollisionType::_SPHERE:
			{
				if (leftType == CollisionType::_OBB)
					isCol = OBBvsSPHERE((OBB*)left->shape, (SPHERE*)right->shape);
				else
					isCol = OBBvsSPHERE((OBB*)right->shape, (SPHERE*)left->shape);
				break;
			}
			default:
				break;
			}

			bool isContained = left->Search(right);
			if (true == isCol)
			{
				if (false == isContained)
				{
					left->enter = true;
					left->otherCols.insert({ right,true });

					left->OnCollisionEnter(right);
					right->OnCollisionEnter(left);

					right->debugColor = { 1,0,0,1 };
					left->debugColor = { 1,0,0,1 };
				}
				else
				{
					left->OnCollisionStay(right);
					right->OnCollisionStay(left);

					left->stay = true;
					left->enter = false;
				}
			}
			else
			{
				if (false == isContained)
				{
					left->free = true;
					left->exit = false;
				}
				else
				{
					left->OnCollisionExit(right);
					right->OnCollisionExit(left);

					left->exit = true;
					left->stay = false;
					left->otherCols.erase(right);

					right->debugColor = { 0,1,0,1 };
					left->debugColor = { 0,1,0,1 };
				}
			}
		}
	}
}

bool CCollisionList::AABBvsAABB(AABB* _aabb1, AABB* _aabb2) const
{
	return _aabb1->box.Intersects(_aabb2->box);
}

bool CCollisionList::SPHEREvsSPHERE(SPHERE* _sphere1, SPHERE* _sphere2) const
{
	return _sphere1->sphere.Intersects(_sphere2->sphere);
}

bool CCollisionList::AABBvsSPHERE(AABB* _aabb, SPHERE* _sphere)
{
	return _aabb->box.Intersects(_sphere->sphere);
}

bool CCollisionList::AABBvsOBB(AABB* _aabb, OBB* _obb)
{
	return _aabb->box.Intersects(_obb->box);
}

bool CCollisionList::OBBvsOBB(OBB* _obb1, OBB* _obb2)
{
	return _obb1->box.Intersects(_obb2->box);
}

bool CCollisionList::OBBvsSPHERE(OBB* _obb, SPHERE* _sphere)
{
	return _obb->box.Intersects(_sphere->sphere);
}