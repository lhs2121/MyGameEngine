#include "Pre.h"
#include "Player.h"

Player::~Player()
{
}

void Player::Awake()
{
	SetName("player");
	m_pRenderer->LoadTexture(L"Assets\\Texture\\fg.jpg");
	pSp = m_pRenderer->CreateSpriteObject("asd",L"fg.jpg",4,4);
	pSp2 = m_pRenderer->CreateSpriteObject("asd2", L"asdf.jpg", 4, 4);
	transform.SetLocalPosition({ 50,50,});
	transform.SetLocalScale({ 64,64 });
	//pRigid = CreateChild<RigidBody2D>();

	pColider = CreateChild<Colider>();
	pColider->SetCollisionType(CollisionType::_AABB);
	GetScene()->AddCollision(pColider);
	//pColider->SetColOrder(Layer::Collision::PLAYER);
}

void Player::Update(float _deltaTime)
{
	static bool one = true;
	if (one)
	{
		pSp->UpdateAnimation(_deltaTime);
		m_pRenderer->DrawSprite(transform.matWorld, pSp);
	}
	else
	{
		pSp2->UpdateAnimation(_deltaTime);
		m_pRenderer->DrawSprite(transform.matWorld, pSp2);
	}
	if (GetKeyDown('1'))
	{
		one = true;
	}
	if (GetKeyDown('2'))
	{
		one = false;
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
	if (GetKeyPress('F'))
	{
		transform.AddLocalRotation({ 0,5 * _deltaTime });
	}
	if (GetKeyPress('H'))
	{
		transform.AddLocalRotation({ 0,0,5 * _deltaTime });
	}
	if (GetKeyDown('R'))
	{
		if (pRigid)
			pRigid->velocity = { 0,0 };

		transform.SetLocalPosition({ 200,200 });
		transform.SetLocalRotation({ 0,0,0 });
	}
}

void Player::OnCollisionEnter(Colider* _Other)
{
	int a = 0;
}
