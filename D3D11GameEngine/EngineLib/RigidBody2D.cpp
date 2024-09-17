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
	//�ϴ� �����ݸ����� ������������ �װ� ��Ÿ���ϰ�
	//mgsin��Ÿ�� �����׷����� �Ѵٸ� �����̵� ������ �ƴϵ� ��¥������ Ȱ����
	//�� �´� �����µ� ���ؾ���
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
