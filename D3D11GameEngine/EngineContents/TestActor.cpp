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
	if (EngineCore::GetMainInput().IsUp('a'))
	{
	    Renderer->Transform.AddRotation({ 10,10,10});	
	}

	
}
