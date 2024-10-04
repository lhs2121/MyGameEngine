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
		case ColType::_AABB2D | ColType::_AABB2D:
			isCol = AABB2DvsAABB2D((AABB2D*)_col->shape, (AABB2D*)other->shape);
			break;
		case ColType::_SPHERE2D | ColType::_SPHERE2D:
			isCol = SPHERE2DvsSPHERE2D((SPHERE2D*)_col->shape, (SPHERE2D*)other->shape);
			break;
		case ColType::_OBB2D | ColType::_OBB2D:
			isCol = OBB2DvsOBB2D((OBB2D*)_col->shape, (OBB2D*)other->shape);
			break;
		case ColType::_AABB2D | ColType::_SPHERE2D :
		{
			if(leftType == ColType::_AABB2D)
				isCol = AABB2DvsSPHERE2D((AABB2D*)_col->shape, (SPHERE2D*)other->shape);
			else
				isCol = AABB2DvsSPHERE2D((AABB2D*)other->shape, (SPHERE2D*)_col->shape);
			break;
		}
		case ColType::_AABB2D | ColType::_OBB2D:
		{
			if (leftType == ColType::_AABB2D)
				isCol = AABB2DvsOBB2D((AABB2D*)_col->shape, (OBB2D*)other->shape);
			else
				isCol = AABB2DvsOBB2D((AABB2D*)other->shape, (OBB2D*)_col->shape);
			break;
		}
		case ColType::_OBB2D | ColType::_SPHERE2D:
		{
			if (leftType == ColType::_OBB2D)
				isCol = OBB2DvsSPHERE2D((OBB2D*)_col->shape, (SPHERE2D*)other->shape);
			else
				isCol = OBB2DvsSPHERE2D((OBB2D*)other->shape, (SPHERE2D*)_col->shape);
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

bool ColGroup::AABB2DvsAABB2D(AABB2D* _aabb1, AABB2D* _aabb2) const
{
	return _aabb1->box.Intersects(_aabb2->box);
}

bool ColGroup::SPHERE2DvsSPHERE2D(SPHERE2D* _sphere1, SPHERE2D* _sphere2) const
{
	return _sphere1->sphere.Intersects(_sphere2->sphere);
}

bool ColGroup::AABB2DvsSPHERE2D(AABB2D* _aabb, SPHERE2D* _sphere)
{
	return _aabb->box.Intersects(_sphere->sphere);
}

bool ColGroup::AABB2DvsOBB2D(AABB2D* _aabb, OBB2D* _obb)
{
	return _aabb->box.Intersects(_obb->box);
}

bool ColGroup::OBB2DvsOBB2D(OBB2D* _obb1, OBB2D* _obb2)
{
	return _obb1->box.Intersects(_obb2->box);
}

bool ColGroup::OBB2DvsSPHERE2D(OBB2D* _obb, SPHERE2D* _sphere)
{
	return _obb->box.Intersects(_sphere->sphere);
}
