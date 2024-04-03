#pragma once
#include <geBase\EngineMath.h>
#include <string>
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
		m_WinPos = Value;
	}

	inline void SetWinSize(const float4 Value)
	{
		m_WinSize = Value;
	}

	inline void SetWinTitle(const std::string Value)
	{
		m_WinTitle = Value;
	}

	inline void SetHinstance(const HINSTANCE _Hinst)
	{
		m_Hinst = _Hinst;
	}

	HINSTANCE GetHinstance() const
	{
		return m_Hinst;
	}

	HWND& GetHwnd()
	{
		return m_Hwnd;
	}
	float4 GetWindowSize()
	{
		return m_WinSize;
	}

	float4 GetWindowPos()
	{
		return m_WinPos;
	}

	std::string GetWindowTitle()
	{
		return m_WinTitle;
	}

private:
	HINSTANCE m_Hinst;
	HWND m_Hwnd;

	std::string m_WinTitle;
	float4 m_WinSize;
	float4 m_WinPos;
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	void Register();
	void Create();

};

