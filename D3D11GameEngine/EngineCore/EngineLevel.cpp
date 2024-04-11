#include "Pre.h"
#include "EngineLevel.h"

EngineLevel::EngineLevel()
{
}

EngineLevel::~EngineLevel()
{
}

void EngineLevel::Start()
{
}

void EngineLevel::Update(float _Delta)
{
	for (EngineObject* Object : ChildList)
	{
		Object->Update(_Delta);
	}
}
