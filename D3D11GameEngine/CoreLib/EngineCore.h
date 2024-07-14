#pragma once
#include <EngineBaseLib\EngineBaseLib\IEngineBase.h>
#include <EngineMediaLib\EngineMediaLib\IEngineMedia.h>
#include <EngineD3DResourceLib\EngineD3DResourceLib\IEngineD3D11.h>
#include "CoreLibAPI.h"
#include "EngineLevel.h"

class EngineCore : public ICore
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

	ID3D11Device* GetDevice() override
	{
		return MainDevice->GetDevice();
	}
	ID3D11DeviceContext* GetContext() override
	{
		return MainDevice->GetContext();
	}
	IEngineWindow* GetMainWindow() override
	{
		return MainWindow;
	}
	IEngineD3DManager* GetMainD3DManager() override
	{
		return MainD3DManager;
	}

	ILevel* CreateLevel(const char* _Name, ILevel* _NewLevel) override;
	void ChangeLevel(const char* _Name) override;
	void DeleteAllLevel() override;

	bool IsDown(int KeyCode) override
	{
		return MainInput->IsDown(KeyCode);
	}
	bool IsPress(int KeyCode) override
	{
		return MainInput->IsPress(KeyCode);
	}
	bool IsUp(int KeyCode) override
	{
		return MainInput->IsUp(KeyCode);
	}
	bool IsFree(int KeyCode) override
	{
		return MainInput->IsFree(KeyCode);
	}

	void EngineStart(const char* _WindowTitle, float4 _WindowPos, float4 _WindowSize, HINSTANCE _hInstance, IObject* _CoreObject) override;
	void EngineUpdate() override;
	void EngineRelease() override;
private:
	EngineTime MainTime;
	IEngineWindow* MainWindow;
	IEngineInput* MainInput;
	IEngineDevice* MainDevice;
	IEngineD3DManager* MainD3DManager;
	IObject* CoreObject;
	EngineLevel* CurLevel;

	std::map<const char*, EngineLevel*> AllLevel;
};
