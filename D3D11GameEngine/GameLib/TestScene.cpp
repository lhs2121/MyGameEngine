#include "Pre.h"
#include "TestScene.h"
#include "Player.h"
#include "Back.h"
#include "Ground.h"
#include <EngineLib/QuadTree.h>

void TestScene::Awake()
{
	pQuadRoot = CreateChild<CQuadTree>();
	pQuadRoot->Init(0,0, 200, 200, 2);
	pQuadRoot->DivideToMaxLevel();
	a = CreateChild<Player>();
	Input::AddUser(a);
	Input::AddUser(this);
}

void TestScene::Update(float _deltaTime)
{
}
