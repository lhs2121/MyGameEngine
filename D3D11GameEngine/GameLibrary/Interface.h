#pragma once
#include <EngineLibrary/Engine.h>
#include "TestScene.h"

class GameStater : public Initializer
{
public:
	void CreateAllScene(Engine* pEngine) override
	{
		pEngine->CreateScene<TestScene>("Scene001");
		pEngine->LoadScene("Scene001");
	}
};