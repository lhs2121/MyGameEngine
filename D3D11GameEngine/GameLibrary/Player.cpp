#include "pch.h"
#include "Player.h"

Player::~Player()
{
}

void Player::Awake()
{
	SetName("player");

	m_pRenderer->LoadTexture(L"Assets\\Texture\\fg.jpg");

	pSp = m_pRenderer->CreateSpriteObject("asd",L"fg.jpg",4,4);

	m_transform.SetLocalPosition({ 500,0,});
	m_transform.SetLocalScale({ 20,20 });

	CreateCollision(&pCol);

	GetScene()->m_pCollisionList.push_back(pCol);
	pCol->UpdateTransform(&m_transform);
}

void Player::Update(float _deltaTime)
{
	float x = m_transform.vecWorldPosition.m128_f32[0];
	float y = m_transform.vecWorldPosition.m128_f32[1];
	m_pRenderer->DrawFont(L"ㅎㅇ난 게임엔진이야", x, y, 1000, 1000);
	pCol->UpdateTransform(&m_transform);

	pSp->UpdateAnimation(_deltaTime);
	m_pRenderer->DrawSprite(m_transform.matWorld, pSp);

	if (GetKeyPress('A'))
	{
		m_transform.AddLocalPosition({ -300 * _deltaTime,0 });
	}
	if (GetKeyPress('D'))
	{
		m_transform.AddLocalPosition({ 300 * _deltaTime,0 });
	}
	if (GetKeyPress('W'))
	{
		m_transform.AddLocalPosition({ 0,300 * _deltaTime });
	}
	if (GetKeyPress('S'))
	{
		m_transform.AddLocalPosition({ 0,-300 * _deltaTime });
	}
	if (GetKeyPress('F'))
	{
		m_transform.AddLocalRotation({ 0,5 * _deltaTime });
	}
	if (GetKeyPress('H'))
	{
		m_transform.AddLocalRotation({ 0,0,5 * _deltaTime });
	}
	if (GetKeyDown('R'))
	{
		m_transform.SetLocalPosition({ 200,200 });
		m_transform.SetLocalRotation({ 0,0,0 });
	}
}

void Player::OnCollisionEnter(Colider* _Other)
{
	int a = 0;
}
