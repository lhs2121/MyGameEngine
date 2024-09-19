#include "Pre.h"
#include "Player.h"

void Player::Awake()
{
	pSpriteRenderer = CreateChild<SpriteRenderer>();
	Resource::CreateTexture("Character/stand.dds");
	pSpriteRenderer->GetMaterial()->pTexture = Resource::FindTexture("stand");
	pSpriteRenderer->CreateAnimation(4, 1, 1.0f);

	pRigid = CreateChild<RigidBody2D>();
	transform.SetLocalPos({ 200,200 });
	transform.SetLocalScale({ 64,64 });

	pColider = CreateChild<Colider>();
	pColider->SetColOrder(Layer::Collision::PLAYER);

	CreateEngineTime(&time);
	time->Init();
}

void Player::Update(float _deltaTime)
{
	pColider->Collision(Layer::Collision::GROUND);

	if (GetKeyPress('A'))
	{
		transform.position.x += -50 * _deltaTime;
	}
	if (GetKeyPress('D'))
	{
		transform.position.x += 50 * _deltaTime;
	}
	if (GetKeyPress('G'))
	{
		transform.AddLocalRotation({ 0,0,10 * _deltaTime });
	}
	if (GetKeyDown('R'))
	{
		pRigid->velocity = { 0,0 };
		transform.SetLocalPos({ 200,200 });
		transform.SetLocalRotation({ 0,0,0 });
	}
}
