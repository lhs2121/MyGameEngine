#pragma once
#include "GameAPI.h"

class GameStarter : public IGameStarter
{
public:
	void GameStart(ICore* MainCore) override;
};