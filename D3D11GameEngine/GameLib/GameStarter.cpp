#include "Pre.h"
#include "GameStarter.h"
#include <CoreLib/Engine.h>
#include "TestLevel.h"

void GameStarter::GameStart(ICore* MainCore)
{
	Engine* Core = (Engine*)MainCore;
	Core->CreateLevel("TestLevel", new TestLevel());
	Core->ChangeLevel("TestLevel");
}
