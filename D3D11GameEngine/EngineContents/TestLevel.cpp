#include "Pre.h"
#include "TestLevel.h"
#include "TestActor.h"

TestLevel::TestLevel()
{
}

TestLevel::~TestLevel()
{
}

void TestLevel::Start()
{
	CreateActor(sizeof(TestActor), new TestActor());
}

void TestLevel::Update(float _Delta)
{
}
