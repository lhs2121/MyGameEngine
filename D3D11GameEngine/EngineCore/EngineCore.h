#pragma once
#include <EngineBaseLib\EngineBaseLib\IEngineBase.h>
#include <EngineMediaLib\EngineMediaLib\IEngineMedia.h>
#include <EngineD3DResourceLib\EngineD3DResourceLib\IEngineD3D11.h>
#include "EngineLevel.h"
#include <map>

#define KeyIsDown(KeyCode) EngineCore::IsDown(KeyCode)
#define KeyIsPress(KeyCode) EngineCore::IsPress(KeyCode)
#define KeyIsUp(KeyCode) EngineCore::IsUp(KeyCode)
#define KeyIsFree(KeyCode) EngineCore::IsFree(KeyCode)

class EngineLevel;
class EngineObject;
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
	static IEngineWindow* GetMainWindow()
	{
		return MainWindow;
	}
	static IEngineD3DManager* GetMainD3DManager()
	{
		return MainD3DManager;
	}

	template<typename LevelType>
	static EngineLevel* CreateLevel(const char* LevelName)
	{
		EngineLevel* NewLevel = new LevelType();
		NewLevel->SetName(LevelName);
		NewLevel->Start();

		AllLevel.insert(std::make_pair(LevelName, NewLevel));
		return NewLevel;
	}

	static void DeleteAllLevel()
	{
		for (std::pair<const char*, EngineLevel*> pair : AllLevel)
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

	static void ChangeLevel(const char* LevelName)
	{
		if(AllLevel.end() != AllLevel.find(LevelName))
		{
			CurLevel = AllLevel[LevelName];
		}
	}

	static void EngineStart(const char* _WindowTitle, float4 _WindowPos, float4 _WindowSize, HINSTANCE _hInstance, EngineObject* _CoreObject);
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
	static EngineTime MainTime;

	static IEngineWindow* MainWindow;
	static IEngineInput* MainInput;

	static IEngineDevice* MainDevice;
	static IEngineD3DManager* MainD3DManager;

	static EngineObject* CoreObject;
	static EngineLevel* CurLevel;

	static std::map<const char*, EngineLevel*> AllLevel;
};