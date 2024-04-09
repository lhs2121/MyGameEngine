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
	CreateActor<TestActor>();
}

void TestLevel::Update(float _Delta)
{
}
