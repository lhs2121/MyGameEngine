#pragma once
#include "EngineWindow.h"
#include "EngineDevice.h"

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

	static void EngineStart(HINSTANCE inst);

	static void CoreStart();
	static void CoreUpdate();
	static void CoreRelease();

	static EngineWindow MainWindow;
	static EngineDevice MainDevice;
};