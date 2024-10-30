#include "Pre.h"
#include "Scene.h"
#include "Colider.h"
#include "QuadTree.h"

Colider::Colider()
{
	Naming::ReturnName("Object");
	name = Naming::GetName("Colider");
}

Colider::~Colider()
{
	if (shape != nullptr)
		delete shape;
}

void Colider::Awake()
{
	shape = new AABB();
	shape->Update(transform);
}

void Colider::Update(float _deltaTime)
{
	m_pRenderer->DrawRect(transform.matWorld, { 1,0,0,1 });
	shape->Update(transform);
}

void Colider::SetCollisionType(CollisionType _Type)
{
	collisionType = _Type;
	const char* meshName = nullptr;

	switch (collisionType)
	{
	case CollisionType::_AABB:
		meshName = "Box2D";
		if (shape)
		{
			delete shape;
			shape = new AABB;
		}
		break;

	case CollisionType::_OBB:
		meshName = "Box2D";
		if (shape)
		{
			delete shape;
			shape = new OBB;
		}
		break;

	case CollisionType::_SPHERE:
		meshName = "Sphere2D";
		if (shape)
		{
			delete shape;
			shape = new SPHERE;
		}
		break;

	default:
		break;
	}
	shape->Update(transform);
}

bool Colider::Collision(Colider* pOther)
{
	Colider* left = this;
	Colider* right = pOther;

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
			left->OnCollisionEnter(right);
			right->OnCollisionEnter(left);

			left->otherCols.insert({ right,true });
			right->debugColor = { 1,0,0,1 };
			left->debugColor = { 1,0,0,1 };
		}
		else
		{
			left->OnCollisionStay(right);
			right->OnCollisionStay(left);

		}
	}
	else
	{
		if (isContained)
		{
			left->OnCollisionExit(right);
			right->OnCollisionExit(left);

			left->otherCols.erase(right);
			right->debugColor = { 0,1,0,1 };
			left->debugColor = { 0,1,0,1 };
		}
	}

	return isCol;
}

bool Colider::SimpleCollision(Colider* pOther)
{
	Colider* left = this;
	Colider* right = pOther;

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

	return isCol;
}


bool Colider::AABBvsAABB(AABB* _aabb1, AABB* _aabb2) const
{
	return _aabb1->box.Intersects(_aabb2->box);
}

bool Colider::SPHEREvsSPHERE(SPHERE* _sphere1, SPHERE* _sphere2) const
{
	return _sphere1->sphere.Intersects(_sphere2->sphere);
}

bool Colider::AABBvsSPHERE(AABB* _aabb, SPHERE* _sphere)
{
	return _aabb->box.Intersects(_sphere->sphere);
}

bool Colider::AABBvsOBB(AABB* _aabb, OBB* _obb)
{
	return _aabb->box.Intersects(_obb->box);
}

bool Colider::OBBvsOBB(OBB* _obb1, OBB* _obb2)
{
	return _obb1->box.Intersects(_obb2->box);
}

bool Colider::OBBvsSPHERE(OBB* _obb, SPHERE* _sphere)
{
	return _obb->box.Intersects(_sphere->sphere);
}

bool Colider::Search(Colider* _other)
{
	if (otherCols.find(_other) != otherCols.end())
	{
		return true;
	}
	return false;
}

