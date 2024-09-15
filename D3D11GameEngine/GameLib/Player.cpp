#include "Pre.h"
#include "Player.h"

void Player::Awake()
{
	pSpriteRenderer = CreateChild<SpriteRenderer>();
	Resource::CreateTexture("Character/stand.dds");
	pSpriteRenderer->GetMaterial()->pTexture = Resource::FindTexture("stand");
	pSpriteRenderer->CreateAnimation(4, 1, 1.0f);

	pRigid = CreateChild<RigidBody2D>();
	transform.SetLocalScale({ 128,128 });

	pColider2D = CreateChild<Colider2D>();
	pColider2D->SetColType(ColType::Circle2D);
}

void Player::Update(float _deltaTime)
{
	//if (pColider2D->IsCollision())
	//{
	//	int a = 0;
	//}

	if (GetKeyPress('Z'))
	{
		transform.AddLocalRotation({ 100 * _deltaTime,0,0 });
	}
	if (GetKeyPress('X'))
	{
		transform.AddLocalRotation({ 0,100 * _deltaTime,0 });
	}
	if (GetKeyPress('C'))
	{
		transform.AddLocalRotation({ 0,0,100 * _deltaTime });
	}

	float4 dir = { 0,0 };
	if (GetKeyPress('W'))
	{
		dir += { 0,1 };
	}
	if (GetKeyPress('A'))
	{
		dir += { -1,0 };
	}
	if (GetKeyPress('S'))
	{
		dir += { 0,-1 };
	}
	if (GetKeyPress('D'))
	{
		dir += { 1,0 };
	}
	if (pRigid != nullptr)
	{
		pRigid->velocity = dir * _deltaTime * 100;
	}

	if (GetKeyPress('Q'))
	{
		GetScene()->GetMainCamera()->transform.AddLocalPos({ 0,0,100 * _deltaTime });
	}
	if (GetKeyPress('E'))
	{
		GetScene()->GetMainCamera()->transform.AddLocalPos({ 0,0,-100 * _deltaTime });
	}
	if (GetKeyDown('R'))
	{
		transform.SetLocalPos({ 0,0,0 });
		transform.SetLocalRotation({ 0,0,0 });
	}
}
