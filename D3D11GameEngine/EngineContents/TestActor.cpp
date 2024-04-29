#include "Pre.h"
#include "TestActor.h"
#include "EngineCore\EngineCamera.h"

TestActor::TestActor()
{
}

TestActor::~TestActor()
{
}

void TestActor::Start()
{
	GetLevel()->GetMainCamera()->SetProjectionType(ProjectionType::Perspective);
	Renderer = CreateComponent<EngineRenderer>();
	Renderer->Transform.SetScale({ 100,100,100 });
}

void TestActor::Update(float _Delta)
{
	if (EngineInput::IsPress('1'))
	{
		Renderer->Transform.AddRotation({ 100 * _Delta,0,0 });
	}
	if (EngineInput::IsPress('2'))
	{
		Renderer->Transform.AddRotation({ 0,-100 * _Delta,0 });
	}
	if (EngineInput::IsPress('3'))
	{
		Renderer->Transform.AddRotation({ 0,0,100 * _Delta });
	}
	if (EngineInput::IsPress('W'))
	{
		Renderer->Transform.AddPos({ 0,100 * _Delta,0 });
	}
	if (EngineInput::IsPress('A'))
	{
		Renderer->Transform.AddPos({ -100 * _Delta,0,0 });
	}
	if (EngineInput::IsPress('S'))
	{
		Renderer->Transform.AddPos({ 0,-100 * _Delta,0 });
	}
	if (EngineInput::IsPress('D'))
	{
		Renderer->Transform.AddPos({ 100 * _Delta,0,0 });
	}
	if (EngineInput::IsPress('Q'))
	{
		Renderer->Transform.AddPos({ 0,0,100 * _Delta });
	}
	if (EngineInput::IsPress('E'))
	{
		Renderer->Transform.AddPos({ 0,0,-100 * _Delta });
	}
	if (EngineInput::IsDown('R'))
	{
		Renderer->Transform.SetPos({ 0,0,0 });
	}
}
