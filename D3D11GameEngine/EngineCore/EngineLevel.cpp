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
	for (EngineObject* Object : AllObject)
	{
		Object->Update(_Delta);
	}
}
