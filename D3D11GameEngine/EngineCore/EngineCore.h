#pragma once
#include <d3d11.h>
#include <EngineWindow\EngineWindow.h>
#include <EngineInputLib\include\IEngineInput.h>
#include <EngineD3DResourceLib\include\IEngineD3DResource.h>
#include "EngineRenderer.h"
#include "EngineLevel.h"

#define KeyIsDown(KeyCode) EngineCore::IsDown(KeyCode)
#define KeyIsPress(KeyCode) EngineCore::IsPress(KeyCode)
#define KeyIsUp(KeyCode) EngineCore::IsUp(KeyCode)
#define KeyIsFree(KeyCode) EngineCore::IsFree(KeyCode)

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
		return MainDevice->GetDevice();
	}
	static ID3D11DeviceContext* GetContext()
	{
		return MainDevice->GetContext();
	}
	static EngineWindow& GetMainWindow()
	{
		return MainWindow;
	}
	static IEngineD3DResourceManager* GetMainResourceManager()
	{
		return MainResourceManager;
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

	static void DeleteAllLevel()
	{
		for (std::pair<std::string, EngineLevel*> pair : AllLevel)
		{
			EngineLevel* LevelPtr = pair.second;
			if (LevelPtr != nullptr)
			{
				delete LevelPtr;
				LevelPtr = nullptr;
			}
		}
		AllLevel.clear();
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

	static bool IsDown(int KeyCode)
	{
		return MainInput->IsDown(KeyCode);
	}
	static bool IsPress(int KeyCode)
	{
		return MainInput->IsPress(KeyCode);
	}
	static bool IsUp(int KeyCode)
	{
		return MainInput->IsUp(KeyCode);
	}
	static bool IsFree(int KeyCode)
	{
		return MainInput->IsFree(KeyCode);
	}
private:

	static EngineObject* CoreObject;
	static EngineLevel* CurLevel;
	static EngineWindow MainWindow;
	static IEngineDevice* MainDevice;
	static EngineTime MainTime;
	static IEngineInput* MainInput;
	static IEngineD3DResourceManager* MainResourceManager;
	static std::map<std::string, EngineLevel*> AllLevel;
};