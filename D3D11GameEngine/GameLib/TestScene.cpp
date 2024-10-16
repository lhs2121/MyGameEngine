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

	Device::SetClearColor({ 0.4f,0.5f,0.4f,1.0f });
	GetMainCamera()->SetProjectionType(ProjectionType::Perspective);

	//CreateChild<Back>();
	CreateChild<Ground>();
	a = CreateChild<Player>();

	Input::AddUser(a);
	Input::AddUser(this);
}

void TestScene::Update(float _deltaTime)
{
	//float zvalue = GetMainCamera()->transform.localPosition.z;
	//GetMainCamera()->transform.SetLocalPosition({ a->transform.worldPosition.x, a->transform.worldPosition.y, zvalue });
	if (GetKeyPress('Q'))
	{
		GetMainCamera()->transform.AddLocalPosition({ 0,0,100 * _deltaTime });
	}
	if (GetKeyPress('E'))
	{
		GetMainCamera()->transform.AddLocalPosition({ 0,0,-100 * _deltaTime });
	}
}
