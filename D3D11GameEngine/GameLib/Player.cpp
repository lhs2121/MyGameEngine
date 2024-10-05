#include "Pre.h"
#include "Player.h"

void Player::Awake()
{
	SetName("player");

	pSpriteRenderer = CreateChild<SpriteRenderer>();
	pSpriteRenderer->SetRenderOrder(Layer::Render::PLAYER);

	Resource::CreateTexture("Character/stand.dds");
	pSpriteRenderer->GetMaterial()->pTexture = Resource::FindTexture("stand");
	pSpriteRenderer->CreateAnimation(4, 1, 1.0f);

	transform.SetLocalPosition({ 200,200,0 });
	transform.SetLocalScale({ 64,64,1 });

	//pRigid = CreateChild<RigidBody2D>();

	pColider = CreateChild<Colider>();
	pColider->SetCollisionType(CollisionType::_OBB);
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
	if (GetKeyDown('1'))
	{
		pColider->SetCollisionType(CollisionType::_AABB);
	}
	if (GetKeyDown('2'))
	{
		pColider->SetCollisionType(CollisionType::_OBB);
	}
	if (GetKeyDown('3'))
	{
		pColider->SetCollisionType(CollisionType::_SPHERE);
	}
	if (GetKeyPress('A'))
	{
		transform.AddLocalPosition({ -100 * _deltaTime,0 });
	}
	if (GetKeyPress('D'))
	{
		transform.AddLocalPosition({ 100 * _deltaTime,0 });
	}
	if (GetKeyPress('W'))
	{
		transform.AddLocalPosition({ 0,100 * _deltaTime });
	}
	if (GetKeyPress('S'))
	{
		transform.AddLocalPosition({ 0,-100 * _deltaTime });
	}
	if (GetKeyDown('R'))
	{
		if (pRigid)
			pRigid->velocity = { 0,0 };

		transform.SetLocalPosition({ 200,200 });
		transform.SetLocalRotation({ 0,0,0 });
	}
}
