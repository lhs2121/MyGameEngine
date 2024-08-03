#include "Pre.h"
#include "GameAPI.h"
#include "GameStarter.h"

void CreateGameStarter(IGameStarter** ppIGameStarter)
{
	*ppIGameStarter = new GameStarter();
}

void DeleteGameStarter(IGameStarter* pInterface)
{
	GameStarter* castptr = (GameStarter*)pInterface;
	delete castptr;
}
