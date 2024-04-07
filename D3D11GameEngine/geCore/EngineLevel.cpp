#include "Pre.h"
#include "EngineLevel.h"

EngineLevel::EngineLevel()
{
}

EngineLevel::~EngineLevel()
{
}

EngineLevel* EngineLevel::CreateLevel(std::string LevelName)
{
	EngineLevel* NewLevel = new EngineLevel();
	NewLevel->SetName(LevelName);
	NewLevel->Start();
	return NewLevel;
}

void EngineLevel::Start()
{
}

void EngineLevel::Update(float _Delta)
{
}
