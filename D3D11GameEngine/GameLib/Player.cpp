#include "Pre.h"
#include "Player.h"

void Player::Awake()
{
	SetName("player");
	transform.SetLocalPos({ 200,200,0 });
	transform.SetLocalScale({ 64,64 });

	pSpriteRenderer = CreateChild<SpriteRenderer>();
	pSpriteRenderer->SetRenderOrder(Layer::Render::PLAYER);

	Resource::CreateTexture("Character/stand.dds");
	pSpriteRenderer->GetMaterial()->pTexture = Resource::FindTexture("stand");
	pSpriteRenderer->CreateAnimation(4, 1, 1.0f);

	//pRigid = CreateChild<RigidBody2D>();

	pColider = CreateChild<Colider>();
	pColider->SetColType(ColType::_SPHERE2D);
	pColider->SetColOrder(Layer::Collision::PLAYER);
}

void Player::Update(float _deltaTime)
{
	pColider->Collision(Layer::Collision::GROUND);
	if (pColider->state == ColState::ENTER)
	{
		int a = 0;
	}
	if (pColider->state == ColState::EXIT)
	{
		int a = 0;
	}
	if (GetKeyPress('A'))
	{
		transform.AddLocalPos({ -100 * _deltaTime,0 });
	}
	if (GetKeyPress('D'))
	{
		transform.AddLocalPos({ 100 * _deltaTime,0 });
	}
	if (GetKeyPress('W'))
	{
		transform.AddLocalPos({ 0,100 * _deltaTime });
	}
	if (GetKeyPress('S'))
	{
		transform.AddLocalPos({ 0,-100 * _deltaTime });
	}
	if (GetKeyDown('R'))
	{
		if (pRigid)
			pRigid->velocity = { 0,0 };

		transform.SetLocalPos({ 200,200 });
		transform.SetLocalRotation({ 0,0,0 });
	}
}
