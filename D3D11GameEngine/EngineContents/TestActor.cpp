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
}

void TestActor::Update(float _Delta)
{
	Renderer->Transform.AddPos({ 1,0 });
	float4x4 wvp = Renderer->Transform.WorldViewProjectionMat;
	int a = 0;
}
