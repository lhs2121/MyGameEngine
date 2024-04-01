#pragma once
#include <gePlatform\EngineWindow.h>
#include "EngineDevice.h"
#include "EngineRenderer.h"

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
	static void EngineStart(HINSTANCE inst);

	static void CoreStart();
	static void CoreUpdate();
	static void CoreRelease();

private:
	static EngineRenderer TestRenderer;
	static EngineWindow MainWindow;
	static EngineDevice MainDevice;
};