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
				isCol = AABB2DvsAABB2D(_col, other);
			}
			else if (other->colType == ColType::SPHERE2D)
			{
				isCol = AABB2DvsSPHERE2D(_col, other);
			}
			else if (other->colType == ColType::OBB2D)
			{
				isCol = AABB2DvsOBB2D(_col, other);
			}
		}
		else if (_col->colType == ColType::SPHERE2D)
		{
			if (other->colType == ColType::AABB2D)
			{
				isCol = AABB2DvsSPHERE2D(other, _col);
			}
			else if (other->colType == ColType::SPHERE2D)
			{
				isCol = SPHERE2DvsSPHERE2D(_col, other);
			}
			else if (other->colType == ColType::OBB2D)
			{
				isCol = OBB2DvsSPHERE2D(other, _col);
			}
		}
		else if (_col->colType == ColType::OBB2D)
		{
			if (other->colType == ColType::AABB2D)
			{
				isCol = AABB2DvsOBB2D(other, _col);
			}
			else if (other->colType == ColType::SPHERE2D)
			{
				isCol = OBB2DvsSPHERE2D(_col, other);
			}
			else if (other->colType == ColType::OBB2D)
			{
				isCol = OBB2DvsOBB2D(_col, other);
			}
		}

		bool isContained = _col->Search(other);
		if (true == isCol)
		{
			if (false == isContained)
			{
				_col->state = ColState::ENTER;
				_col->otherColiders.push_back(other);
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
				_col->otherColiders.remove(other);
			}
		}
	}

}

bool ColGroup::AABB2DvsAABB2D(Colider* _aabb1, Colider* _aabb2) const
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

bool ColGroup::SPHERE2DvsSPHERE2D(Colider* _sphere1, Colider* _sphere2) const
{
	float Sum = _sphere1->radius + _sphere2->radius;
	float4 Pos1 = _sphere1->transform.position + _sphere1->transform.localPosition;
	float4 Pos2 = _sphere2->transform.position + _sphere2->transform.localPosition;
	float Distance = Pos1.Distance(Pos2);
	if (Distance > Sum)
	{
		return false;
	}
	return true;
}

bool ColGroup::AABB2DvsSPHERE2D(Colider* _aabb, Colider* _sphere)
{
	float4 circlePos = _sphere->transform.worldPosition;

	float4 Near;
	Near.x = EngineMath::Clamp(circlePos.x, _aabb->right, _aabb->left);
	Near.y = EngineMath::Clamp(circlePos.y, _aabb->top, _aabb->bottom);

	float distance = Near.Distance(circlePos);

	if (distance <= _sphere->radius)
	{
		return true;
	}
	return false;
}

bool ColGroup::AABB2DvsOBB2D(Colider* _aabb, Colider* _obb)
{
	return false;
}

bool ColGroup::OBB2DvsOBB2D(Colider* _obb1, Colider* _obb2)
{
	return false;
}

bool ColGroup::OBB2DvsSPHERE2D(Colider* _obb, Colider* _sphere)
{
	return false;
}
