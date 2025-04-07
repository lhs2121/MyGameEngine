#include "pch.h"
#include "TestScene.h"
#include "Player.h"
#include "Back.h"
#include "Ground.h"

void TestScene::Awake()
{
	//UseQuadTree();
	//a = CreateChild<Player>();
	//CreateChild<Ground>();

	

	//m_pInputObject->AddUser(a);
	m_pInputObject->AddUser(this);
	
}

void TestScene::Update(float _deltaTime)
{
	m_pRenderer->DrawRibbon();
	//m_pRenderer->DrawFont(L"asdfdas", 0, 0, 100, 200);
}
