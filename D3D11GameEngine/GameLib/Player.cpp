#include "Pre.h"
#include "Player.h"

void Player::Awake()
{
	pSpriteRenderer = CreateChild<SpriteRenderer>();
	Resource::CreateTexture("Character/stand.dds");
	pSpriteRenderer->GetMaterial()->pTexture = Resource::FindTexture("stand");
	pSpriteRenderer->CreateAnimation(4, 1, 1.0f);

	pRigid = CreateChild<RigidBody2D>();
	transform.SetLocalPos({ 0,200 });
	transform.SetLocalScale({ 128,128 });

	pColider2D = CreateChild<Colider2D>();
	pColider2D->SetColType(ColType::Circle2D);
}

void Player::Update(float _deltaTime)
{
	float4 dir = { 0,0 };

	if (GetKeyPress('A'))
	{
		dir += { -1,0 };
	}
	if (GetKeyPress('D'))
	{
		dir += { 1,0 };
	}


	if (GetKeyDown('R'))
	{
		transform.SetLocalPos({ 0,0,0 });
		transform.SetLocalRotation({ 0,0,0 });
	}
}
