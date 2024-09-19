#include "Pre.h"
#include "RigidBody2D.h"
#include "math.h"

void RigidBody2D::Start()
{
	parentObject = GetParent();
	parentCol = parentObject->GetChild<Colider>();
}

void RigidBody2D::Update(float _deltaTime)
{
}

void RigidBody2D::AddForce(float4 _force)
{
	
}
void RigidBody2D::LateUpdate(float _deltaTime)
{
	//일단 콜리전의 enter stay out을 구해야함!!!!!!!!
	// 그리고 enter에서 충격력을 구하고
	// stay에서 수직항력
	// 미끄러지는힘 정지마찰력 운동마찰력은 그 후에
	//일단 지면콜리전의 각도를구하자 그걸 세타라하고
	//mgsin세타를 수직항력으로 한다면 빗면이든 빗면이 아니든 알짜힘으로 활용함
	//아 맞다 마찰력도 더해야함

	float4 f_total;
	float4 f_slide;
	float4 f_friction;

	static bool enter = false;
	if (parentCol->IsCollision())
	{
		if (enter == false)
		{
			float4 f_col = { 0,600000};
			f_total += f_col;
		    enter = true;
		}
		float4 f_static_friction;
		float4 f_dynamic_friction;
		float theta = 25 * DegToRad;

		float s_N = gravity * cosf(theta);
		float s_slide = gravity * sinf(theta);
		float s_max_static_slide = static_friction * s_N;
		float s_dynamic_slide = dynamic_friction * s_N;

		float4 dir_slide = -float4::Resolution(1, theta);
		float4 dir_friction = -dir_slide;

		f_slide = dir_slide * float4::Resolution(s_slide, theta);

		if (s_slide <= s_max_static_slide)
		{
			f_friction = -f_slide;
		}
		else
		{
			f_friction = dir_friction * float4::Resolution(s_dynamic_slide, theta);
		}
	}
	else
	{
		f_total.y = -gravity;
	}

	f_total += f_slide + f_friction;

	acceleration = f_total;
	float4 deltaAccel = acceleration * _deltaTime;
	velocity += deltaAccel;
	float4 displacement = velocity * _deltaTime;
	parentObject->transform.AddLocalPos(displacement);
}
