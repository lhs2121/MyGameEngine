#include "Pre.h"
#include "TestLevel.h"
#include "Player.h"

void TestLevel::Awake()
{
	GetMainCamera()->SetProjectionType(ProjectionType::Perspective);
	a = CreateGameObject<Player>();
	b = CreateGameObject<Player>();
	b->transform.SetPos({ 150,150 });

	auto c = a->GetComponent<Renderer>();
	c->SetRenderOrder(500);

	mainInput->AddUser(a);
}

void TestLevel::Update(float _deltaTime)
{
	int a = 0;
}
