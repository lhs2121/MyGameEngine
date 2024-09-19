#include "Pre.h"
#include "Ground.h"

void Ground::Awake()
{	
	pColider = CreateChild<Colider>();
	pColider->SetColType(ColType::AABB2D);
	pColider->transform.SetLocalPos({ 0,-150 });
	pColider->SetColOrder(Layer::Collision::GROUND);
	pColider->SetName("dirt");

	for (size_t i = 0; i < 99; i++)
	{
		pColider = CreateChild<Colider>();
		pColider->SetColType(ColType::AABB2D);
		pColider->transform.SetLocalPos({ 0,-150 });
		pColider->SetColOrder(Layer::Collision::GROUND);
	}

	transform.SetLocalScale({ 700,60 });
	transform.SetLocalRotation({ 0,0,0 });
}

void Ground::Update(float _deltaTime)
{


}
