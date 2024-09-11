#pragma once

class Engine;
struct SceneManager
{
	virtual void CreateAllScene(Engine* pMainEngine) = 0;
};