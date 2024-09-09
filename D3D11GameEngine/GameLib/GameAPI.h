#pragma once

struct IGameStarter
{
	virtual void GameStart(IEngine* MainCore) = 0;
};
extern "C" GameAPI void CreateGameStarter(IGameStarter** ppInterface);
extern "C" GameAPI void DeleteGameStarter(IGameStarter* pInterface);