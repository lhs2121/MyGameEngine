#include "Pre.h"
#include "GameObject.h"
#include "RigidBody2D.h"

void RigidBody2D::Start()
{
	parentCol = GetParent()->GetComponent<Colider2D>();
}

void RigidBody2D::Update(float _deltaTime)
{
	if (parentCol->isCollision)
	{
		parentObject->transform.AddLocalPos({ -5 * _deltaTime ,0 });
	}
}
