#include "Pre.h"
#include "Scene.h"
#include "Colider.h"
#include "Renderer.h"

void Colider::Awake()
{
	GetScene()->AddCollision(this);

	debugRenderer = CreateChild<Renderer>();
	debugRenderer->SetRenderOrder(999);
	debugRenderer->SetMesh("Box2D");
	debugRenderer->SetMaterial("WireFrame");
}

void Colider::Update(float _deltaTime)
{
	radius = transform.worldScale.hx();
	right = transform.worldPosition.x + transform.worldScale.hx();
	left = transform.worldPosition.x - transform.worldScale.hx();
	top = transform.worldPosition.y + transform.worldScale.hy();
	bottom = transform.worldPosition.y - transform.worldScale.hy();
}

void Colider::Release()
{
	int a = 0;
}

void Colider::SetColOrder(int _order)
{
	GetScene()->SetColOrder(this, _order);
}

void Colider::SetColType(ColType _Type)
{
	colType = _Type; 
	const char* meshName = nullptr;

	switch (colType)
	{
	case ColType::AABB2D:
		meshName = "Box2D";
		break;
	case ColType::AABB3D:
		meshName = "Box3D";
		break;
	case ColType::OBB2D:
		meshName = "Box2D";
		break;
	case ColType::OBB3D:
		meshName = "Box3D";
		break;
	case ColType::SPHERE2D:
		meshName = "Sphere2D";
		break;
	case ColType::SPHERE3D:
		meshName = "Sphere3D";
		break;
	default:
		break;
	}
	debugRenderer->SetMesh(meshName);
}

void Colider::Collision(int _otherOrder)
{
	ColGroup* otherGroup = GetScene()->GetGroup(_otherOrder);
	if(otherGroup != nullptr)
		parentGroup->Collision(this,otherGroup);
}

bool Colider::Search(Colider* _other)
{
	if (otherCols.find(_other) != otherCols.end())
	{
		return true;
	}
	return false;
}

