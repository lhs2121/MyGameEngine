 #pragma once
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

class EngineWindow 
{
public:
	EngineWindow();
	~EngineWindow();

	EngineWindow(const EngineWindow& _Other) = delete;
	EngineWindow(EngineWindow&& _Other) noexcept = delete;
	EngineWindow& operator=(const EngineWindow& _Other) = delete;
	EngineWindow& operator=(EngineWindow&& _Other) noexcept = delete;

	void OpenWindow();
	void SetHinstance(HINSTANCE _HInst)
	{
		HInst = _HInst;
	}

	HINSTANCE GetHinstance()
	{
		return HInst;
	}

	HWND GetHwnd()
	{
		return Hwnd;
	}

	HDC GetHdc()
	{
		return Hdc;
	}
	void MessageLoop();
private:
	HINSTANCE HInst;
	HDC Hdc;
	HWND Hwnd;

	void InitInstance();
	void MyRegisterClass();
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
};

