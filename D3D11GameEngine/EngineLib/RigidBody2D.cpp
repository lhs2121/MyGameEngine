#include "Pre.h"
#include "RigidBody2D.h"

void RigidBody2D::Start()
{
	parentCol = GetParent()->GetChild<Colider2D>();
}

void RigidBody2D::Update(float _deltaTime)
{
}

void RigidBody2D::LateUpdate(float _deltaTime)
{

	GetParent()->transform.AddLocalPos(velocity);
}
