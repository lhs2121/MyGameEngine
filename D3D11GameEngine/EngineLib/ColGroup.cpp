#include "Pre.h"
#include "ColGroup.h"


void ColGroup::Collision(Colider* _col, ColGroup* _group)
{
	for (Colider* other : _group->colList)
	{
		bool isCol = false;
		if (_col->colType == ColType::AABB2D)
		{
			if (other->colType == ColType::AABB2D)
			{
				isCol = AABB2DvsAABB2D((AABB2D*)_col->shape, (AABB2D*)other->shape);
			}
			else if (other->colType == ColType::SPHERE2D)
			{
				isCol = AABB2DvsSPHERE2D((AABB2D*)_col->shape, (SPHERE2D*)other->shape);
			}
			else if (other->colType == ColType::OBB2D)
			{
				isCol = AABB2DvsOBB2D((AABB2D*)_col->shape, (OBB2D*)other->shape);
			}
		}
		else if (_col->colType == ColType::SPHERE2D)
		{
			if (other->colType == ColType::AABB2D)
			{
				isCol = AABB2DvsSPHERE2D((AABB2D*)other->shape, (SPHERE2D*)_col->shape);
			}
			else if (other->colType == ColType::SPHERE2D)
			{
				isCol = SPHERE2DvsSPHERE2D((SPHERE2D*)_col->shape, (SPHERE2D*)other->shape);
			}
			else if (other->colType == ColType::OBB2D)
			{
				isCol = OBB2DvsSPHERE2D((OBB2D*)other->shape, (SPHERE2D*)_col->shape);
			}
		}
		else if (_col->colType == ColType::OBB2D)
		{
			if (other->colType == ColType::AABB2D)
			{
				isCol = AABB2DvsOBB2D((AABB2D*)other->shape, (OBB2D*)_col->shape);
			}
			else if (other->colType == ColType::SPHERE2D)
			{
				isCol = OBB2DvsSPHERE2D((OBB2D*)_col->shape, (SPHERE2D*)other->shape);
			}
			else if (other->colType == ColType::OBB2D)
			{
				isCol = OBB2DvsOBB2D((OBB2D*)_col->shape, (OBB2D*)other->shape);
			}
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
	if (_aabb2->right < _aabb1->left)
	{
		return false;
	}
	if (_aabb2->left > _aabb1->right)
	{
		return false;
	}

	//여기까지 왔으면 x축은 충돌했다

	if (_aabb2->top < _aabb1->bottom)
	{
		return false;
	}
	if (_aabb2->bottom > _aabb1->top)
	{
		return false;
	}

	return true;
}

bool ColGroup::SPHERE2DvsSPHERE2D(SPHERE2D* _sphere1, SPHERE2D* _sphere2) const
{
	float radiusSum = _sphere1->radius + _sphere2->radius;
	float distance = _sphere1->center.distance(_sphere2->center);

	if (distance > radiusSum)
	{
		return false;
	}
	return true;
}

bool ColGroup::AABB2DvsSPHERE2D(AABB2D* _aabb, SPHERE2D* _sphere)
{
	float4 Near;
	Near.x = math::clamp(_sphere->center.x, _aabb->right, _aabb->left);
	Near.y = math::clamp(_sphere->center.y, _aabb->top, _aabb->bottom);

	float distance = Near.distance(_sphere->center); 

	if (distance <= _sphere->radius)
	{
		return true;
	}
	return false;
}

bool ColGroup::AABB2DvsOBB2D(AABB2D* _aabb, OBB2D* _obb)
{
	return false;
}

bool ColGroup::OBB2DvsOBB2D(OBB2D* _obb1, OBB2D* _obb2)
{
	float4 horizontalVector1 = _obb1->rightTop - _obb1->leftTop;
	float4 verticalVector1 = _obb1->rightTop - _obb1->rightBottom;

	float4 horizontalVector2 = _obb2->rightTop - _obb2->leftTop;
	float4 verticalVector2 = _obb2->rightTop - _obb2->rightBottom;

	float4 centerVector = _obb1->center - _obb2->center;

	float4 horizontalAxis1 = float4::normalize(horizontalVector1);
	float4 verticalAxis1 = float4::normalize(verticalVector1);

	float len1 = abs(float4::dot(horizontalVector1, horizontalAxis1)/2);
	float len2 = abs(float4::dot(horizontalVector2, horizontalAxis1)/2);
	float dis = abs(float4::dot(centerVector, horizontalAxis1));

	if (dis > (len1 + len2))
	{
		return false;
	}

	float len3 = abs(float4::dot(verticalVector1, verticalAxis1)/2);
	float len4 = abs(float4::dot(verticalVector2, verticalAxis1)/2);
	float dis2 = abs(float4::dot(centerVector, verticalAxis1));

	if (dis2 > (len3 + len4))
	{
		return false;
	}

	// 첫번째 obb의 모든축으로 완료

	float4 horizontalAxis2 = float4::normalize(horizontalVector2);
	float4 verticalAxis2 = float4::normalize(verticalVector2);

	float len5 = abs(float4::dot(horizontalVector1, horizontalAxis2) / 2);
	float len6 = abs(float4::dot(horizontalVector2, horizontalAxis2) / 2);
	float dis3 = abs(float4::dot(centerVector, horizontalAxis2));

	if (dis3 > (len5 + len6))
	{
		return false;
	}

	float len7 = abs(float4::dot(verticalVector1, verticalAxis2) / 2);
	float len8 = abs(float4::dot(verticalVector2, verticalAxis2) / 2);
	float dis4 = abs(float4::dot(centerVector, verticalAxis2));

	if (dis4 > (len7 + len8))
	{
		return false;
	}

	return true;
}



bool ColGroup::OBB2DvsSPHERE2D(OBB2D* _obb, SPHERE2D* _sphere)
{
	return false;
}
