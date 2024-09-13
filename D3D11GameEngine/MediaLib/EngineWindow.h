#pragma once
#include "MediaAPI.h"

class EngineWindow
{
public:
	EngineWindow()
	{
		mainWindow = this;
	}
	static EngineWindow* mainWindow;

	void Init(const char* _title, float4 _pos, float4 _size, const HINSTANCE _hInstance, IEngine* _pEngine);
	void MessageLoop();
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	const char*  title;
	float4       pos;
	float4       size;
	HINSTANCE    hInstance;
	HWND         hWnd;
    IEngine*     pEngine;
};

