#pragma once
#include "CoreAPI.h"
#include "EngineLevel.h"

struct IGameStarter;
class  EngineCore : public ICore
{
public:
	EngineLevel*   CreateLevel(const char* _Name, EngineLevel* _NewLevel);
	void           ChangeLevel(const char* _Name);
	void           DeleteAllLevel();
				   
	void           EngineStart(const char* _WindowTitle, float4 _WindowPos, float4 _WindowSize, HINSTANCE _hInstance, IGameStarter* _Starter) override;
	void           EngineUpdate() override;
	void           EngineRelease() override;

private:
	IGameStarter* Starter;
	EngineLevel*  CurLevel;
	EngineHashMap AllLevel;

	IEngineTime* MainTime = nullptr;
	IEngineWindow* MainWindow = nullptr;
	IEngineInput* MainInput = nullptr;
	IDevice* MainDevice = nullptr;
	IResManager* MainResManager = nullptr;
};
