#include "Pre.h"
#include "TestLevel.h"
#include "TestActor.h"

void TestLevel::Awake()
{
	GetMainCamera()->SetProjectionType(ProjectionType::Perspective);
	a = (TestActor*)CreateObject(new TestActor());
	b = (TestActor*)CreateObject(new TestActor());
	b->Transform.SetPos({ 0,150 });

	a->SetColType(ColType::Circle2D);
	b->SetColType(ColType::Circle2D);

	Input->AddUser(a);
}

void TestLevel::Update(float _Delta)
{
	EngineLevel::Update(_Delta);
	float4x4 at = a->Transform.WorldMat;
	float4x4 bt = b->Transform.WorldMat;
}
