#include "Pre.h"
#include "EngineWindow.h"
#include <EngineLib/EngineAPI.h>

EngineWindow::EngineWindow()
{
}

EngineWindow::~EngineWindow()
{
}

void EngineWindow::Init(const char* _WindowTile, float4 _WindowPos, float4 _WindowSize, const HINSTANCE _hInst, IEngine* _pMainEngine)
{

	WindowTitle = _WindowTile;

	WindowPos = _WindowPos;

	WindowSize = _WindowSize;

	hInst = _hInst;

	pMainEngine = _pMainEngine;
	
	{
		WNDCLASSEXA wcex;

		wcex.cbSize = sizeof(WNDCLASSEXA);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = EngineWindow::WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInst;
		wcex.hIcon = nullptr;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = "ClinetWindow";
		wcex.hIconSm = nullptr;

		ATOM A = RegisterClassExA(&wcex);
	}

	{
		hWnd = CreateWindowA("ClinetWindow", "WindowTitle", WS_OVERLAPPEDWINDOW,
			WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), nullptr, nullptr, hInst, nullptr);

		if (!hWnd)
		{
			EngineDebug::MsgBoxAssert("윈도우 만들기 실패");
		}

		if (hWnd != 0)
		{
			ShowWindow(hWnd, SW_SHOW);
			UpdateWindow(hWnd);
		}
	}

}

LRESULT CALLBACK EngineWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void EngineWindow::MessageLoop()
{
	MSG msg = {};

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			pMainEngine->EngineUpdate();
		}
	}

	pMainEngine->EngineRelease();
}

const char* EngineWindow::GetWindowTitle()
{
	return WindowTitle;
}

float4 EngineWindow::GetWindowSize() const
{
	return WindowSize;
}

float4 EngineWindow::GetWindowPos() const
{
	return WindowPos;
}

HINSTANCE EngineWindow::GethInst() const
{
	return hInst;
}

HWND* EngineWindow::GethWnd() 
{
	return &hWnd;
}
