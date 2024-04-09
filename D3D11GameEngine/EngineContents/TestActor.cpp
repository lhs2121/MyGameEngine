#include "Pre.h"
#include "TestActor.h"

TestActor::TestActor()
{
}

TestActor::~TestActor()
{
}

void TestActor::Start()
{
	CreateComponent<EngineRenderer>();
}

void TestActor::Update(float _Delta)
{
}
