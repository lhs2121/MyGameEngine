#include "Pre.h"
#include "GameSceneManager.h"
#include <EngineLib/Engine.h>
#include "TestScene.h"

void GameSceneManager::CreateAllScene(Engine* pMainEngine)
{
	pMainEngine->CreateScene<TestScene>("Scene001");
	pMainEngine->LoadScene("Scene001");
}
