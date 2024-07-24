#pragma once
#include <common\declspec.h>

struct IGameStarter
{
	virtual void GameStart() = 0;
};
extern "C" GameAPI void CreateGameStarter(IGameStarter** ppIGameStarter);