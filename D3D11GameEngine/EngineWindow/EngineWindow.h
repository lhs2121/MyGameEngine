#pragma once
#include <Windows.h>
class EngineWindow
{
public:
	// constrcuter destructer
	EngineWindow();
	~EngineWindow();

	// constrcuter destructer
	EngineWindow(const EngineWindow& _Other) = delete;
	EngineWindow(EngineWindow&& _Other) noexcept = delete;
	EngineWindow& operator=(const EngineWindow& _Other) = delete;
	EngineWindow& operator=(EngineWindow&& _Other) noexcept = delete;

	void OpenWindow();
	void MessageLoop();

	inline void SetWinPos(const float4 Value)
	{
		WindowPos = Value;
	}

	inline void SetWinSize(const float4 Value)
	{
		WindowSize = Value;
	}

	inline void SetWinTitle(const char* Value)
	{
		WindowTitle = Value;
	}

	inline void SetHinstance(const HINSTANCE _Hinst)
	{
		hInstance = _Hinst;
	}

	HINSTANCE GetHinstance() const
	{
		return hInstance;
	}

	HWND* GetHwnd()
	{
		return &hWnd;
	}
	float4 GetWindowSize()
	{
		return WindowSize;
	}

	float4 GetWindowPos()
	{
		return WindowPos;
	}

	EngineString GetWindowTitle()
	{
		return WindowTitle;
	}

private:
	HINSTANCE hInstance;
	HWND hWnd;

	float4 WindowPos;
	float4 WindowSize;
	EngineString WindowTitle;

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	void Register();
	void Create();

};

