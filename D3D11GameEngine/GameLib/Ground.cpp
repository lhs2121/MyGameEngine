#include "Pre.h"
#include "Ground.h"

void Ground::Awake()
{	
	SetName("Ground");
	transform.SetLocalScale({ 64,64 });

	pColider = CreateChild<Colider>();
	pColider->SetName("dirt");
	//pColider->SetColOrder(Layer::Collision::GROUND);
	pColider->transform.SetLocalPosition({ 64,64 });
	pColider->SetCollisionType(CollisionType::_OBB);

	GetScene()->IntoQuadTree(pColider);
	Input::AddUser(this);
}

void Ground::Update(float _deltaTime)
{
}
