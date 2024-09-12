#include "Pre.h"
#include "TestScene.h"
#include "Player.h"

void TestScene::Awake()
{
	GetMainCamera()->SetProjectionType(ProjectionType::Perspective);

	a = CreateGameObject<Player>();
	mainInput->AddUser(a);
}

void TestScene::Update(float _deltaTime)
{
}
