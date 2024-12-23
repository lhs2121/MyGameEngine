#include "pch.h"
#include "Ground.h"

void Ground::Awake()
{	
	SetName("Ground");
	m_transform.SetLocalScale({ 64,64 });
	m_pRenderer->LoadTexture(L"Assets\\Texture\\asdf.jpg");
	pSp = m_pRenderer->CreateSpriteObject("asdf", L"asdf.jpg", 4, 4);
	m_transform.SetLocalPosition({ 0,0,});
	m_transform.SetLocalScale({ 50,50 });
	CreateCollision(&pCol);
	GetScene()->m_pCollisionList.push_back(pCol);
	pCol->UpdateTransform(&m_transform);
}

void Ground::Update(float _deltaTime)
{
	float x = (float)rand() / RAND_MAX * 2.0f - 1.0f;
	float y = (float)rand() / RAND_MAX * 2.0f - 1.0f;

	float length = sqrt((x) * (x) + (y) * (y));
	if (length > 0) 
	{
		x /= length;
		y /= length;
	}
	
	
	m_transform.AddLocalPosition({ x * 1000 * _deltaTime,0 });
	m_transform.AddLocalPosition({ 0, -y * 1000 * _deltaTime });
	pCol->UpdateTransform(&m_transform);
	pSp->UpdateAnimation(_deltaTime);
	m_pRenderer->DrawSprite(m_transform.m_matWorld, pSp);
}
