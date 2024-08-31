#include "Pre.h"
#include "GameStarter.h"
#include <CoreLib/EngineCore.h>
#include "TestLevel.h"

void GameStarter::GameStart(ICore* MainCore)
{
	EngineCore* Core = (EngineCore*)MainCore;
	Core->CreateLevel("TestLevel", new TestLevel());
	Core->ChangeLevel("TestLevel");
}
