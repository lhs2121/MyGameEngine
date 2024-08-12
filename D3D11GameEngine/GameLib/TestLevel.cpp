#include "Pre.h"
#include "TestLevel.h"
#include "TestActor.h"

void TestLevel::Awake()
{
	GetMainCamera()->SetProjectionType(ProjectionType::Perspective);
	TestActor* a = (TestActor*)CreateActor(new TestActor());
	TestActor* b = (TestActor * )CreateActor(new TestActor());
	a->SetName("parent");
	b->SetName("child");

	b->SetParent(a);

}

void TestLevel::Update(float _Delta)
{
}
