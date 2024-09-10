#include "Pre.h"
#include "Player.h"
#include "Resource.h"

void Player::Awake()
{
	Resource::mainResourceManager = mainResManager;
	ITexture* tex = Resource::Load<ITexture>("Sample.png");

	pSpriteRenderer = AddComponent<SpriteRenderer>();
	pSpriteRenderer->SetMesh("Box3D");
	pSpriteRenderer->GetMaterial()->SetTexture("Sample");
	pSpriteRenderer->CreateAnimation(2, 2, 1.0f);

	pColider2D = AddComponent<Colider2D>();
	pColider2D->SetColScale({ 1,1,1,1 });

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
		transform.AddPos({ 0,5 * _deltaTime,0 });
	}
	if (GetKeyPress('A'))
	{
		transform.AddPos({ -5 * _deltaTime,0,0 });
	}
	if (GetKeyPress('S'))
	{
		transform.AddPos({ 0,-5 * _deltaTime,0 });
	}
	if (GetKeyPress('D'))
	{
		transform.AddPos({ 5 * _deltaTime,0,0 });
	}
	if (GetKeyPress('Q'))
	{
		transform.AddPos({ 0,0,20 * _deltaTime });
	}
	if (GetKeyPress('E'))
	{
		transform.AddPos({ 0,0,-20 * _deltaTime });
	}
	if (GetKeyDown('R'))
	{
		transform.SetPos({ 0,0,0 });
		transform.SetRotation({ 0,0,0 });
	}
}
