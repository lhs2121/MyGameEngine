#include "Pre.h"
#include "TestLevel.h"
#include "TestActor.h"

void TestLevel::Awake()
{
	GetMainCamera()->SetProjectionType(ProjectionType::Perspective);
	a = (TestActor*)CreateActor(new TestActor());
	b = (TestActor*)CreateActor(new TestActor());
	c = (TestActor*)CreateActor(new TestActor());
	d = (TestActor*)CreateActor(new TestActor());

	a->SetColScale({ 100,100 });
	b->SetColScale({ 150,150 });
	c->SetColScale({ 200,200 });
	d->SetColScale({ 250,250 });


}

void TestLevel::Update(float _Delta)
{
	EngineLevel::Update(_Delta);
	float4x4 at = a->Transform.WorldMat;
	float4x4 bt = b->Transform.WorldMat;
}
