#include "Pre.h"
#include "RigidBody.h"
#include "math.h"

void RigidBody::Start()
{
	parentObject = GetParent();
	parentCol = parentObject->GetChild<Colider>();
}

void RigidBody::Update(float _deltaTime)
{
}

void RigidBody::AddForce(float4 _force)
{
	
}
void RigidBody::LateUpdate(float _deltaTime)
{
	float4 f_total;
	float4 f_slide;
	float4 f_friction;


	f_total += f_slide + f_friction;

	acceleration = f_total;
	float4 deltaAccel = acceleration * _deltaTime;
	velocity += deltaAccel;
	float4 displacement = velocity * _deltaTime;
	//parentObject->transform.AddLocalPosition(displacement);
}
