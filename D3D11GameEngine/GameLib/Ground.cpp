#include "Pre.h"
#include "Ground.h"

void Ground::Awake()
{	
	SetName("Ground");
	transform.SetLocalScale({ 700,60 });

	pColider = CreateChild<Colider>();
	pColider->SetName("dirt");
	pColider->SetColType(ColType::_OBB2D);
	pColider->SetColOrder(Layer::Collision::GROUND);

	pColider->transform.SetLocalPos({ 0,-150 });
	Input::AddUser(this);
}

void Ground::Update(float _deltaTime)
{
	if (GetKeyPress('C'))
	{
		transform.AddLocalRotation({ 0,0,1 * _deltaTime });
	}
	if (GetKeyPress('X'))
	{
		transform.AddLocalRotation({ 0,0,-1 * _deltaTime });
	}
	
}
