#include "Pre.h"
#include "RigidBody2D.h"

void RigidBody2D::Start()
{
	parentCol = GetParent()->GetChild<Colider2D>();
}

void RigidBody2D::Update(float _deltaTime)
{

	float speed = 1000.0f;
	if (parentCol->IsCollision())
	{
		GetParent()->transform.AddLocalPos(parentCol->dir * speed * _deltaTime);
	}
}
