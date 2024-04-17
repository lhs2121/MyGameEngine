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
	Renderer->Transform.SetScale({ 100,100,1 });
}

void TestActor::Update(float _Delta)
{
	Renderer->Transform.AddPos({ 50 * _Delta,0 });
}
