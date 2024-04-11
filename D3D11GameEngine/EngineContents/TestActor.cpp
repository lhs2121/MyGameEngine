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
	EngineRenderer* Renderer = CreateComponent<EngineRenderer>();
	EngineLevel* a = Renderer->GetLevel();
}

void TestActor::Update(float _Delta)
{
}
