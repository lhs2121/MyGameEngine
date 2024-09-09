#pragma once
#include "Component.h"
#include "Colider2D.h"

class RigidBody2D : public Component
{
public:
	RigidBody2D() = default;
	~RigidBody2D() = default;

	void Start() override;
	void Update(float _deltaTime) override;
private:
	float4 velocity;
	GameObject* parentGameObject;
	Colider2D* parentCol;
};