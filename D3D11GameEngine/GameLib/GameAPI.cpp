#include "Pre.h"
#include "GameAPI.h"
#include "GameStarter.h"

void CreateGameStarter(IGameStarter** ppIGameStarter)
{
	*ppIGameStarter = new GameStarter();
}