#include "Pre.h"
#include "TestScene.h"
#include "Player.h"

void TestScene::Awake()
{
	GetMainCamera()->SetProjectionType(ProjectionType::Perspective);


	Player* c = CreateChild<Player>();
	c->transform.SetLocalPos({ 40,0,0 });
	c->GetChild<Renderer>()->GetMaterial()->pDepthStencil = Resource::FindDepthStencil("DepthOnWirteOn");

	Player* b = CreateChild<Player>();
	b->transform.SetLocalPos({ 20,0,5 });
	b->GetChild<Renderer>()->GetMaterial()->pDepthStencil = Resource::FindDepthStencil("DepthOnWirteOff");

	Player* a = CreateChild<Player>();
	a->transform.SetLocalPos({ 0,0,10 });
	a->GetChild<Renderer>()->GetMaterial()->pDepthStencil = Resource::FindDepthStencil("DepthOnWirteOn");

	Input::AddUser(a);
}

void TestScene::Update(float _deltaTime)
{
}
