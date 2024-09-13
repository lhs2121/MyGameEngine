#include "Pre.h"
#include "TestScene.h"
#include "Player.h"

void TestScene::Awake()
{
	GetMainCamera()->SetProjectionType(ProjectionType::Orthographic);

	a = CreateGameObject<Player>();
	a->GetComponent<Renderer>()->SetRenderOrder(5);

	Player* b = CreateGameObject<Player>();
	b->transform.SetLocalPos({ 100,100 });
	Input::AddUser(a);
}

void TestScene::Update(float _deltaTime)
{
}
