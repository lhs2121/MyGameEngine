#include "Pre.h"
#include "RigidBody2D.h"
#include "math.h"

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
	//일단 지면콜리전의 각도를구하자 그걸 세타라하고
	//mgsin세타를 수직항력으로 한다면 빗면이든 빗면이 아니든 알짜힘으로 활용함
	//아 맞다 마찰력도 더해야함
	float4 f_total;

	if (parentCol->IsCollision())
	{

		float normalRadian = theta.z* DegToRad;
		float4 f_slide = c_gravity * sinf(normalRadian);
		float4 f_normal = -c_gravity * cos(normalRadian);

		float4 f_friction = c_gravity * cos(normalRadian) * c_friction;
		f_total = f_slide + f_friction + f_normal;
	}
	else
		f_total += c_gravity;
	
	acceleration = f_total;
	velocity += acceleration * _deltaTime;
	float4 displacement = velocity * _deltaTime;
	parentObject->transform.AddLocalPos(displacement);
}
