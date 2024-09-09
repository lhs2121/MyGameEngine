#include "Pre.h"
#include "TestScene.h"
#include "Player.h"

void TestScene::Awake()
{
	GetMainCamera()->SetProjectionType(ProjectionType::Perspective);
	a = CreateGameObject<Player>();
	b = CreateGameObject<Player>();
	b->transform.SetPos({ 150,150 });

	Renderer* c = a->GetComponent<Renderer>();
	c->SetRenderOrder(500);

	mainInput->AddUser(a);
}

void TestScene::Update(float _deltaTime)
{
}
