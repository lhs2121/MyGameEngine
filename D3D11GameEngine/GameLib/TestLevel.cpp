#include "Pre.h"
#include "TestLevel.h"
#include "TestActor.h"

void TestLevel::Awake()
{
	GetMainCamera()->SetProjectionType(ProjectionType::Perspective);
	a = (TestActor*)CreateActor(new TestActor());
	b = (TestActor*)CreateActor(new TestActor());

	b->Transform.SetLocalPos({ 101,100 });
}

void TestLevel::Update(float _Delta)
{
	EngineLevel::Update(_Delta);
	float4x4 at = a->Transform.WorldMat;
	float4x4 bt = b->Transform.WorldMat;
}
