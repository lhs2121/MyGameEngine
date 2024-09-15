#pragma once

#include "Colider2D.h"

class RigidBody2D : public Object
{
public:
	RigidBody2D() = default;
	~RigidBody2D() = default;

	void Start() override;
	void Update(float _deltaTime) override;
	void LateUpdate(float _deltaTime) override;
	float g = -10.0f;
	float4 a = {0.0f,0.0f,0.0f,1.0f};
	float4 velocity = { 0.0f,0.0f,0.0f,1.0f };
private:
	Colider2D* parentCol;
};