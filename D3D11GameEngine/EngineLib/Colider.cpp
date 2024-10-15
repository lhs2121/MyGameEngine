#include "Pre.h"
#include "Scene.h"
#include "Colider.h"
#include "Renderer.h"

Colider::Colider()
{
	Naming::ReturnName("Object");
	name = Naming::GetName("Colider");
}

Colider::~Colider()
{
	if(shape !=nullptr)
		delete shape;
}

void Colider::Awake()
{
	shape = new AABB();
	shape->Update(transform);

	debugRenderer = CreateChild<Renderer>();
	debugRenderer->SetRenderOrder(999);
	debugRenderer->SetMesh("Box2D");
	debugRenderer->SetMaterial("WireFrame");


	base::string cbname = Naming::GetName("DebugRenderer");
	debugRenderer->SetConstantBuffer(cbname.c_str(), &debugColor, sizeof(float4), ShaderType::PS, 1);
}

void Colider::Update(float _deltaTime)
{
	shape->Update(transform);
}

void Colider::Release()
{
	GetScene()->RemoveCollision(this);
}

void Colider::SetColOrder(int _order)
{
	GetScene()->SetColOrder(this, _order);
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
	debugRenderer->SetMesh(meshName);
}

void Colider::Collision(int _otherOrder)
{
	ColGroup* otherGroup = GetScene()->GetGroup(_otherOrder);
	if (otherGroup != nullptr)
		parentGroup->Collision(this, otherGroup);
}

bool Colider::Search(Colider* _other)
{
	if (otherCols.find(_other) != otherCols.end())
	{
		return true;
	}
	return false;
}

