#include "Pre.h"
#include "Ground.h"

void Ground::Awake()
{	
	pColider = CreateChild<Colider>();
	pColider->SetColType(ColType::AABB2D);
	pColider->transform.SetLocalPos({ 0,-150 });
	transform.SetLocalScale({ 700,60 });
	transform.SetLocalRotation({ 0,0,20 });
}

void Ground::Update(float _deltaTime)
{


}
