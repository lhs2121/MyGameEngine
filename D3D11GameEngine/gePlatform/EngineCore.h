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

	static void EngineStart(HINSTANCE inst);

	static void EngineUpdate();

	static EngineWindow& GetMainWindow()
	{
		return MainWindow;
	}

protected:
	static EngineWindow MainWindow;
};