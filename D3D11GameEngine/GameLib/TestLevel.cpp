#include "Pre.h"
#include "TestLevel.h"
#include "TestActor.h"

void TestLevel::Awake()
{
	CreateActor(new TestActor());
}

void TestLevel::Update(float _Delta)
{
}
