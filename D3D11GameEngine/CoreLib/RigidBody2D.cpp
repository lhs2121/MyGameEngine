#include "Pre.h"
#include "GameObject.h"
#include "RigidBody2D.h"

void RigidBody2D::Start()
{
	parentGameObject = GetParent();
	parentCol = parentGameObject->GetComponent<Colider2D>();
}

void RigidBody2D::Update(float _deltaTime)
{
	if (parentCol->isCollision)
	{
		parentGameObject->transform.AddLocalPos({ -5 * _deltaTime ,0 });
	}
}
