#include "Pre.h"
#include "ColGroup.h"


void ColGroup::Collision(Colider* _col, ColGroup* _group)
{
	for (Colider* other : _group->colList)
	{
		bool isCol = false;
		int leftType = _col->colType;
		int rightType = other->colType;
		int combinedType = leftType | rightType;

		switch (combinedType) 
		{
		case ColType::_AABB | ColType::_AABB:
			isCol = AABBvsAABB((AABB*)_col->shape, (AABB*)other->shape);
			break;
		case ColType::_SPHERE | ColType::_SPHERE:
			isCol = SPHEREvsSPHERE((SPHERE*)_col->shape, (SPHERE*)other->shape);
			break;
		case ColType::_OBB | ColType::_OBB:
			isCol = OBBvsOBB((OBB*)_col->shape, (OBB*)other->shape);
			break;
		case ColType::_AABB | ColType::_SPHERE :
		{
			if(leftType == ColType::_AABB)
				isCol = AABBvsSPHERE((AABB*)_col->shape, (SPHERE*)other->shape);
			else
				isCol = AABBvsSPHERE((AABB*)other->shape, (SPHERE*)_col->shape);
			break;
		}
		case ColType::_AABB | ColType::_OBB:
		{
			if (leftType == ColType::_AABB)
				isCol = AABBvsOBB((AABB*)_col->shape, (OBB*)other->shape);
			else
				isCol = AABBvsOBB((AABB*)other->shape, (OBB*)_col->shape);
			break;
		}
		case ColType::_OBB | ColType::_SPHERE:
		{
			if (leftType == ColType::_OBB)
				isCol = OBBvsSPHERE((OBB*)_col->shape, (SPHERE*)other->shape);
			else
				isCol = OBBvsSPHERE((OBB*)other->shape, (SPHERE*)_col->shape);
			break;
		}
		default:
			break;
		}

		bool isContained = _col->Search(other);
		if (true == isCol)
		{
			if (false == isContained)
			{
				_col->state = ColState::ENTER;
				_col->otherCols.insert({ other,true });

				other->debugColor = { 1,0,0,1 };
				_col->debugColor = { 1,0,0,1 };
			}
			else
				_col->state = ColState::STAY;
		}
		else
		{
			if (false == isContained)
			{
				_col->state = ColState::FREE;
			}
			else
			{
				_col->state = ColState::EXIT;
				_col->otherCols.erase(other);

				other->debugColor = { 0,1,0,1 };
				_col->debugColor = { 0,1,0,1 };
			}
		}
	}

}

bool ColGroup::AABBvsAABB(AABB* _aabb1, AABB* _aabb2) const
{
	return _aabb1->box.Intersects(_aabb2->box);
}

bool ColGroup::SPHEREvsSPHERE(SPHERE* _sphere1, SPHERE* _sphere2) const
{
	return _sphere1->sphere.Intersects(_sphere2->sphere);
}

bool ColGroup::AABBvsSPHERE(AABB* _aabb, SPHERE* _sphere)
{
	return _aabb->box.Intersects(_sphere->sphere);
}

bool ColGroup::AABBvsOBB(AABB* _aabb, OBB* _obb)
{
	return _aabb->box.Intersects(_obb->box);
}

bool ColGroup::OBBvsOBB(OBB* _obb1, OBB* _obb2)
{
	return _obb1->box.Intersects(_obb2->box);
}

bool ColGroup::OBBvsSPHERE(OBB* _obb, SPHERE* _sphere)
{
	return _obb->box.Intersects(_sphere->sphere);
}
