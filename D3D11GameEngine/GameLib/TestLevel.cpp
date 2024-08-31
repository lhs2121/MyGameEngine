#include "Pre.h"
#include "TestLevel.h"
#include "TestActor.h"

void TestLevel::Awake()
{
	GetMainCamera()->SetProjectionType(ProjectionType::Perspective);
	a = (TestActor*)CreateActor(new TestActor());
	b = (TestActor*)CreateActor(new TestActor());
	b->Transform.SetPos({ 100,100 });

	a->SetColType(ColType::Circle);
	b->SetColType(ColType::Circle);

	Input->AddUser(a);
}

void TestLevel::Update(float _Delta)
{
	EngineLevel::Update(_Delta);
	float4x4 at = a->Transform.WorldMat;
	float4x4 bt = b->Transform.WorldMat;
}
