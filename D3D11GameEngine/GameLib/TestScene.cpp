#include "Pre.h"
#include "TestScene.h"
#include "Player.h"
#include "Back.h"
#include "Ground.h"

void TestScene::Awake()
{
	UseQuadTree();
	a = CreateChild<Player>();
	//CreateChild<Ground>();
	m_pInputObject->AddUser(a);
	m_pInputObject->AddUser(this);
}

void TestScene::Update(float _deltaTime)
{
}
