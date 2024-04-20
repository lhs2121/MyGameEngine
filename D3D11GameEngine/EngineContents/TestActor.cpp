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
	Renderer->Transform.SetScale({ 100,100,100 });
	Renderer->Transform.SetPos({ 0,0,0 });
	Renderer->Transform.SetRotation({ 0,0,0 });

	Renderer2 = CreateComponent<EngineRenderer>();
	Renderer2->Transform.SetScale({ 100,100,100 });
	Renderer2->Transform.SetPos({ 0,-100,0 });
	Renderer2->Transform.SetRotation({ 0,0,0 });
}

void TestActor::Update(float _Delta)
{
	Renderer->Transform.AddRotation({0,0,100*_Delta });
	Renderer2->Transform.AddPos({ -10 * _Delta,0 });
}
