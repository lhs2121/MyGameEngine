#include "pch.h"
#include "TestScene.h"

TestScene::~TestScene()
{
	delete sprite;
}

void TestScene::Awake()
{
	m_transform.SetLocalPosition({ 0.0f, 0.0f, 0.0f });
	m_transform.SetLocalScale({ 200.0f, 200.0f, 1.0f });
	m_pRenderer->LoadTexture(L"Test.png");
	sprite = m_pRenderer->CreateSpriteObject("test", L"Test.png", 1, 1);

	m_pInputObject->AddUser(this);
	
}

void TestScene::Update(float _deltaTime)
{
	m_pRenderer->DrawSprite(m_transform.m_matWorld, sprite);
}
