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
	//�ϴ� �ݸ����� enter stay out�� ���ؾ���!!!!!!!!
	// �׸��� enter���� ��ݷ��� ���ϰ�
	// stay���� �����׷�
	// �̲��������� ���������� ��������� �� �Ŀ�
	//�ϴ� �����ݸ����� ������������ �װ� ��Ÿ���ϰ�
	//mgsin��Ÿ�� �����׷����� �Ѵٸ� �����̵� ������ �ƴϵ� ��¥������ Ȱ����
	//�� �´� �����µ� ���ؾ���

	float4 f_total;
	float4 f_slide;
	float4 f_friction;
	if (parentCol->transform.worldRotation.z != 0)
	{
	    float4 f_static_friction;
	    float4 f_dynamic_friction;

		float theta = parentCol->transform.worldRotation.z * DegToRad;

		float s_N = gravity * cosf(theta);

		float s_slide = gravity * sinf(theta);

		float s_max_static_slide = static_friction * s_N;

		float s_dynamic_slide = dynamic_friction * s_N;
	

		float4 dir_slide = -float4::Resolution(1, theta);
		float4 dir_friction = -dir_slide;

		f_slide = dir_slide * float4::Resolution(s_slide,theta);

		if (s_slide <= s_max_static_slide)
		{
			f_friction = -f_slide;
		}
		else
		{
			f_friction = dir_friction * float4::Resolution(s_dynamic_slide, theta);
		}
	}


	f_total = f_slide + f_friction;


	
	acceleration = f_total;
	velocity += acceleration * _deltaTime;
	float4 displacement = velocity * _deltaTime;
	parentObject->transform.AddLocalPos(displacement);
}
