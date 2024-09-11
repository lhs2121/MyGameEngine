#pragma once
#include <EngineLib/SceneManager.h>

class GameSceneManager : public SceneManager
{
public:
	void CreateAllScene(Engine* pMainEngine) override;
};