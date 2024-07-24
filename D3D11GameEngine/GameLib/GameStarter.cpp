#include "Pre.h"
#include "GameStarter.h"
#include "TestLevel.h"
#include <CoreLib\Singleton.h>
#include <CoreLib\EngineCore.h>

void GameStarter::GameStart()
{
	MainCore->CreateLevel("TestLevel", new TestLevel());
	MainCore->ChangeLevel("TestLevel");
}
