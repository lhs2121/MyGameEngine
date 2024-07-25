#pragma once

struct IGameStarter
{
	virtual void GameStart() = 0;
};
extern "C" GameAPI void CreateGameStarter(IGameStarter** ppIGameStarter);