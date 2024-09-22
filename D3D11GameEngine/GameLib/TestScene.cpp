#include "Pre.h"
#include "TestScene.h"
#include "Player.h"
#include "Back.h"
#include "Ground.h"

void TestScene::Awake()
{
	Device::SetClearColor({ 0.4,0.5,0.4,1 });
	GetMainCamera()->SetProjectionType(ProjectionType::Perspective);

	CreateChild<Back>();
	CreateChild<Ground>();
	a = CreateChild<Player>();

	Input::AddUser(a);
	Input::AddUser(this);
}

void TestScene::Update(float _deltaTime)
{
	//float zvalue = GetMainCamera()->transform.localPosition.z;
	//GetMainCamera()->transform.SetLocalPos({ a->transform.worldPosition.x, a->transform.worldPosition.y, zvalue });
	if (GetKeyPress('Q'))
	{
		GetMainCamera()->transform.AddLocalPos({ 0,0,100 * _deltaTime });
	}
	if (GetKeyPress('E'))
	{
		GetMainCamera()->transform.AddLocalPos({ 0,0,-100 * _deltaTime });
	}

}
