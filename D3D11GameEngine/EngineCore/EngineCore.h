#pragma once
#include <EngineBase\EngineTime.h>
#include <EngineWindow\EngineWindow.h>
#include "EngineDevice.h"
#include "EngineRenderer.h"
#include "EngineLevel.h"

class EngineCore
{
public:
	// constrcuter destructer
	EngineCore();
	~EngineCore();

	// delete Function
	EngineCore(const EngineCore& _Other) = delete;
	EngineCore(EngineCore&& _Other) noexcept = delete;
	EngineCore& operator=(const EngineCore& _Other) = delete;
	EngineCore& operator=(EngineCore&& _Other) noexcept = delete;

	static ID3D11Device* GetDevice()
	{
		return MainDevice.GetDevice();
	}
	static ID3D11DeviceContext* GetContext()
	{
		return MainDevice.GetContext();
	}
	static EngineWindow& GetMainWindow()
	{
		return MainWindow;
	}

	template<typename LevelType>
	static EngineLevel* CreateLevel(std::string LevelName)
	{
		EngineLevel* NewLevel = new LevelType();
		NewLevel->SetName(LevelName);
		NewLevel->Start();

		AllLevel.insert(std::make_pair(LevelName, NewLevel));
		return NewLevel;
	}

	static void ChangeLevel(std::string LevelName)
	{
		if(AllLevel.end() != AllLevel.find(LevelName))
		{
			CurLevel = AllLevel[LevelName];
		}
	}

	static void EngineStart(HINSTANCE _hInstance, float4 _WindowPos, float4 _WindowSize, std::string _WindowTitle, EngineObject* _CoreObject);
	static void EngineUpdate();
	static void EngineRelease();

private:
	static EngineObject* CoreObject;
	static EngineLevel* CurLevel;
	static EngineWindow MainWindow;
	static EngineDevice MainDevice;
	static EngineTime MainTime;

	static std::map<std::string, EngineLevel*> AllLevel;
};