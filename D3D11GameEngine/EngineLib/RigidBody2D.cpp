#include "Pre.h"
#include "RigidBody2D.h"

void RigidBody2D::Start()
{
	parentCol = GetParent()->GetChild<Colider2D>();
}

void RigidBody2D::Update(float _deltaTime)
{
	if (parentCol->isCollision)
	{
		GetParent()->transform.AddLocalPos({-5 * _deltaTime ,0});
	}
}
