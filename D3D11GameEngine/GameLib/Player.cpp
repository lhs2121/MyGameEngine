#include "Pre.h"
#include "Player.h"

void Player::Awake()
{
	transform.SetLocalPos({ 200,200 });
	transform.SetLocalScale({ 64,64 });

	pSpriteRenderer = CreateChild<SpriteRenderer>();
	pSpriteRenderer->SetRenderOrder(Layer::Render::PLAYER);

	Resource::CreateTexture("Character/stand.dds");
	pSpriteRenderer->GetMaterial()->pTexture = Resource::FindTexture("stand");
	pSpriteRenderer->CreateAnimation(4, 1, 1.0f);

	pRigid = CreateChild<RigidBody2D>();

	pColider = CreateChild<Colider>();
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
