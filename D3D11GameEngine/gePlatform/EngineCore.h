#pragma once

#include "EngineWindow.h"

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

	static void EngineStart(HINSTANCE inst)
	{
		std::string Title;

#ifdef _DEBUG
		Title = "D3D11_Clinet_Debug";
#else
		Title = "D3D11_Clinet_Release";
#endif

#ifdef _WIN64
		Title += "_x64";
#else
		Title += "_x86";
#endif

		MainWindow.SetWinPos({ 50,50 });
		MainWindow.SetWinSize({ 1366,789 });
		MainWindow.SetWinTitle(Title);
		MainWindow.SetHinstance(inst);
		MainWindow.OpenWindow();
		MainWindow.MessageLoop();
	}

	static EngineWindow& GetMainWindow()
	{
		return MainWindow;
	}

protected:
	static EngineWindow MainWindow;
};