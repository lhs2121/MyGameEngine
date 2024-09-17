#include "Pre.h"
#include "RigidBody2D.h"

void RigidBody2D::Start()
{
	parentObject = GetParent();
	parentCol = parentObject->GetChild<Colider2D>();
}

void RigidBody2D::Update(float _deltaTime)
{
}

void RigidBody2D::LateUpdate(float _deltaTime)
{
	float4 f_normal;
	if (parentCol->IsCollision())
	{
		f_normal = -f_gravity * 5;
	}
	

	float4 f_total;
	f_total += f_gravity;
	f_total += f_normal;
	acceleration = f_total;
	velocity += acceleration * _deltaTime;
	float4 displacement = velocity * _deltaTime;
	parentObject->transform.AddLocalPos(displacement);
}
