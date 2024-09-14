#include "Pre.h"
#include "Player.h"

void Player::Awake()
{
	pSpriteRenderer = CreateChild<SpriteRenderer>();
	Resource::CreateTexture("Character/stand.dds");
	pSpriteRenderer->GetMaterial()->pTexture = Resource::FindTexture("stand");
	pSpriteRenderer->CreateAnimation(4, 1, 1.0f);

	transform.SetLocalScale({ 128,128 });
	pColider2D = CreateChild<Colider2D>();
	//pColider2D->SetColType(ColType::Circle2D);
	pRigid = CreateChild<RigidBody2D>();
}

void Player::Update(float _deltaTime)
{
	if (pColider2D->IsCollision())
	{
		int a = 0;
	}
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
	if (GetKeyPress('W'))
	{
		transform.AddLocalPos({ 0, 100 * _deltaTime,0 });
	}
	if (GetKeyPress('A'))
	{
		transform.AddLocalPos({ -100 * _deltaTime,0,0 });
	}
	if (GetKeyPress('S'))
	{
		transform.AddLocalPos({ 0,-100 * _deltaTime,0 });
	}
	if (GetKeyPress('D'))
	{
		transform.AddLocalPos({ 100 * _deltaTime,0,0 });
	}
	if (GetKeyPress('Q'))
	{
		GetScene()->GetMainCamera()->transform.AddLocalPos({0,0,100 * _deltaTime});
	}
	if (GetKeyPress('E'))
	{
		GetScene()->GetMainCamera()->transform.AddLocalPos({ 0,0,-100 * _deltaTime });
	}
	if (GetKeyDown('R'))
	{
		Destroy();
		transform.SetLocalPos({ 0,0,0 });
		transform.SetLocalRotation({ 0,0,0 });
	}
}
