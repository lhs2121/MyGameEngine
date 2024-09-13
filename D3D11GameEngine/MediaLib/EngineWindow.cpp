#include "Pre.h"
#include "EngineWindow.h"
#include <EngineLib/EngineAPI.h>

EngineWindow* EngineWindow::mainWindow = nullptr;

void EngineWindow::Init(const char* _title, float4 _pos, float4 _size, const HINSTANCE _hInstance, IEngine* _pEngine)
{
	title = _title;
	pos = _pos;
	size = _size;
	hInstance = _hInstance;
	pEngine = _pEngine;
	
	{
		WNDCLASSEXA wcex;

		wcex.cbSize = sizeof(WNDCLASSEXA);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = EngineWindow::WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = nullptr;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = "GameWindow";
		wcex.hIconSm = nullptr;

		ATOM A = RegisterClassExA(&wcex);
	}

	{
		hWnd = CreateWindowA("GameWindow", "WindowTitle", WS_OVERLAPPEDWINDOW,
			pos.ix(), pos.iy(), size.ix(), size.iy(), nullptr, nullptr, hInstance, nullptr);

		if (!hWnd)
		{
			Debug::MsgBoxAssert("윈도우 만들기 실패");
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
			pEngine->EngineUpdate();
		}
	}

	pEngine->EngineRelease();
}