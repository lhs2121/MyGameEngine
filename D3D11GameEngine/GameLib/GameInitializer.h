#pragma once
#include <EngineLib/Initializer.h>
#include <EngineLib/Engine.h>
#include "TestScene.h"

class GameInitializer : public Initializer
{
public:
	void CreateAllScene(Engine* pMainEngine) override
	{
		pMainEngine->CreateScene<TestScene>("Scene001");
		pMainEngine->LoadScene("Scene001");
	}
};