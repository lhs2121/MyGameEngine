#include "Pre.h"
#include "TestLevel.h"
#include "TestActor.h"

void TestLevel::Awake()
{
	GetMainCamera()->SetProjectionType(ProjectionType::Perspective);
	a = CreateGameObject<TestActor>(1);
	a->transform.SetPos({ 0,150 });

	mainInput->AddUser(a);
}

void TestLevel::Update(float _deltaTime)
{
	int a = 0;
}
