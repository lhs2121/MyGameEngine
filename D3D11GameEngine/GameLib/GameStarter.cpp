#include "Pre.h"
#include "GameStarter.h"
#include "TestLevel.h"

void GameStarter::GameStart()
{
	MainCore->CreateLevel("TestLevel", new TestLevel());
	MainCore->ChangeLevel("TestLevel");
}
