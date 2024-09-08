#pragma once
#include "CoreAPI.h"
#include "Level.h"

struct IGameStarter;
class  Engine : public ICore
{
public:
	Level*   CreateLevel(const char* _Name, Level* _NewLevel);
	void     ChangeLevel(const char* _Name);

	void     EngineStart(const char* _WindowTitle, float4 _WindowPos, float4 _WindowSize, HINSTANCE _hInstance, IGameStarter* _Starter) override;
	void     EngineUpdate() override;
	void     EngineRelease() override;

private:
	IGameStarter* pGameStarter;
	Level* pCurLevel;
	std::map<EngineString, Level*> allLevel;

	IEngineTime* mainTime = nullptr;
	IEngineWindow* mainWindow = nullptr;
	IEngineInput* mainInput = nullptr;
	IDevice* mainDevice = nullptr;
	IResManager* mainResManager = nullptr;
};
