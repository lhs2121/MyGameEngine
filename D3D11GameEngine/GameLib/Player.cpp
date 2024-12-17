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

	transform.SetLocalPosition({ 500,0,});
	transform.SetLocalScale({ 20,20 });

	CreateCollision(&pCol);

	GetScene()->m_pCollisionList.push_back(pCol);
	pCol->UpdateTransform(&transform);
}

void Player::Update(float _deltaTime)
{
	float x = transform.vecWorldPosition.m128_f32[0];
	float y = transform.vecWorldPosition.m128_f32[1];
	m_pRenderer->DrawFont(L"ㅎㅇ난 게임엔진이야", x, y, 1000, 1000);
	pCol->UpdateTransform(&transform);

	pSp->UpdateAnimation(_deltaTime);
	m_pRenderer->DrawSprite(transform.matWorld, pSp);

	if (GetKeyPress('A'))
	{
		transform.AddLocalPosition({ -300 * _deltaTime,0 });
	}
	if (GetKeyPress('D'))
	{
		transform.AddLocalPosition({ 300 * _deltaTime,0 });
	}
	if (GetKeyPress('W'))
	{
		transform.AddLocalPosition({ 0,300 * _deltaTime });
	}
	if (GetKeyPress('S'))
	{
		transform.AddLocalPosition({ 0,-300 * _deltaTime });
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
		transform.SetLocalPosition({ 200,200 });
		transform.SetLocalRotation({ 0,0,0 });
	}
}

void Player::OnCollisionEnter(Colider* _Other)
{
	int a = 0;
}
