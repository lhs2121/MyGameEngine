#pragma once
#include "CoreAPI.h"
#include "Level.h"

struct IGameStarter;
class  Engine : public ICore
{
public:
	Level*   CreateLevel(const char* _Name, Level* _NewLevel);
	void     ChangeLevel(const char* _Name);
	void     DeleteAllLevel();
			
	void     EngineStart(const char* _WindowTitle, float4 _WindowPos, float4 _WindowSize, HINSTANCE _hInstance, IGameStarter* _Starter) override;
	void     EngineUpdate() override;
	void     EngineRelease() override;

private:
	IGameStarter* Starter;
	Level*  CurLevel;
	EngineHashMap AllLevel;

	IEngineTime* MainTime = nullptr;
	IEngineWindow* MainWindow = nullptr;
	IEngineInput* MainInput = nullptr;
	IDevice* MainDevice = nullptr;
	IResManager* MainResManager = nullptr;
};
