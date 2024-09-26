#include "Pre.h"
#include "Ground.h"

void Ground::Awake()
{	
	SetName("Ground");
	transform.SetLocalScale({ 700,60 });
	transform.SetLocalRotation({ 0,0,25 });

	pColider = CreateChild<Colider>();
	pColider->SetName("dirt");
	pColider->SetColType(ColType::OBB2D);
	pColider->SetColOrder(Layer::Collision::GROUND);

	pColider->transform.SetLocalPos({ 0,-150 });
}

void Ground::Update(float _deltaTime)
{


}
