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
	Renderer->Transform.SetScale({ 500,500,500 });
	Renderer->Transform.SetPos({ 0,0,0 });
	Renderer->Transform.SetRotation({ 0,0,0 });
}

void TestActor::Update(float _Delta)
{
	Renderer->Transform.AddRotation({100* _Delta,100* _Delta,100* _Delta });
}
