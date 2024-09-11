#include "Pre.h"
#include "TestScene.h"
#include "Player.h"

void TestScene::Awake()
{
	GetMainCamera()->SetProjectionType(ProjectionType::Perspective);

	a = CreateGameObject<Player>();

	std::vector<float4> poss = 
	{
		{1.5,0},
		{1.5,1.5},
		{1.5,-1.5},
		{-1.5,0},
		{-1.5,1.5},
		{-1.5,-1.5},
		{0,1.5},
		{0,-1.5},
	};

	std::vector<Player*> players;
	for (size_t i = 0; i < poss.size(); i++)
	{
		Player* player = CreateGameObject<Player>();
		player->transform.SetLocalPos(poss[i]);
		players.push_back(player);
	}

	for (size_t i = 0; i < poss.size(); i++)
	{
		players[i]->SetParent(a);
	}

	mainInput->AddUser(a);
}

void TestScene::Update(float _deltaTime)
{
}
