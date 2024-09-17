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
	float4 acceleration = { 0.0f,0.0f,0.0f,1.0f };
	float4 velocity = { 0.0f,0.0f,0.0f,1.0f };
	float4 theta = { 0.0f,0.0f,1.0f,1.0f };

	float4 c_gravity = { 0.0f,-9.8f,0.0f,1.0f }; //�߷�
	float c_friction = 0.55f; // �������
	float c_m = 1; //����
private:
	Object* parentObject = nullptr;
	Colider2D* parentCol = nullptr;
};