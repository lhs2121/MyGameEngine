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
	Renderer->Transform.SetScale({ 200,200,200 });
	Renderer->Transform.SetPos({ 0,0,0 });
	Renderer->Transform.SetRotation({ -20,0,0 });
}

void TestActor::Update(float _Delta)
{
	Renderer->Transform.AddRotation({ 50 * _Delta,50* _Delta,50 * _Delta });
}
