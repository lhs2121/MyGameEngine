#include "Pre.h"
#include "Player.h"

void Player::Awake()
{
	pSpriteRenderer = AddComponent<SpriteRenderer>();
	Resource::CreateTexture("Character/stand.dds");
	pSpriteRenderer->GetMaterial()->pTexture = Resource::FindTexture("stand");
	pSpriteRenderer->CreateAnimation(4, 1, 1.0f);

	pColider2D = AddComponent<Colider2D>();
	transform.SetScale({ 64,64 });
	pRigid = AddComponent<RigidBody2D>();
}

void Player::Update(float _deltaTime)
{
	if (pColider2D->isCollision)
	{
		int a = 0;
	}
	if (GetKeyPress('Z'))
	{
		transform.AddRotation({ 100 * _deltaTime,0,0 });
	}
	if (GetKeyPress('X'))
	{
		transform.AddRotation({ 0,100 * _deltaTime,0 });
	}
	if (GetKeyPress('C'))
	{
		transform.AddRotation({ 0,0,100 * _deltaTime });
	}
	if (GetKeyPress('W'))
	{
		transform.AddPos({ 0, 100 * _deltaTime,0 });
	}
	if (GetKeyPress('A'))
	{
		transform.AddPos({ -100 * _deltaTime,0,0 });
	}
	if (GetKeyPress('S'))
	{
		transform.AddPos({ 0,-100 * _deltaTime,0 });
	}
	if (GetKeyPress('D'))
	{
		transform.AddPos({ 100 * _deltaTime,0,0 });
	}
	if (GetKeyPress('Q'))
	{
		scene->GetMainCamera()->transform.AddPos({ 0,0,100 * _deltaTime });
	}
	if (GetKeyPress('E'))
	{
		scene->GetMainCamera()->transform.AddPos({ 0,0,-100 * _deltaTime });
	}
	if (GetKeyDown('R'))
	{
		transform.SetPos({ 0,0,0 });
		transform.SetRotation({ 0,0,0 });
	}
}
