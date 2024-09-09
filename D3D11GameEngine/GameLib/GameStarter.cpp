#include "Pre.h"
#include "GameStarter.h"
#include <CoreLib/Engine.h>
#include "TestScene.h"

void GameStarter::GameStart(IEngine* MainCore)
{
	Engine* Core = (Engine*)MainCore;
	Core->CreateScene<TestScene>("Scene001");
	Core->LoadScene("Scene001");
}
