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
	Renderer = CreateComponent<EngineRenderer>();
}

void TestActor::Update(float _Delta)
{
	Renderer;
	Renderer->Transform.AddPos({ 50 * _Delta,0 });
}
