#pragma once
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

class MyWindow
{
public:
	MyWindow() { Inst = this; }
	~MyWindow() {};
	MyWindow(const MyWindow& _Other) = delete;
	MyWindow(MyWindow&& _Other) noexcept = delete;
	MyWindow& operator=(const MyWindow& _Other) = delete;
	MyWindow& operator=(MyWindow&& _Other) noexcept = delete;

	static MyWindow* Inst;

	void OpenWindow();
	void SetHinstance(HINSTANCE _hInst)
	{
		hInst = _hInst;
	}

	HINSTANCE GetHinstance()
	{
		return hInst;
	}

	HWND GetHwnd()
	{
		return hwnd;
	}

	HDC GetHdc()
	{
		return hdc;
	}
	void MessageLoop();
private:
	HINSTANCE hInst;
	HDC hdc;
	HWND hwnd;

	void InitInstance();
	void MyRegisterClass();


	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
};

