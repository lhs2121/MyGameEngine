#include "Pre.h"
#include <EngineCore/EngineCore.h>

EngineWindow::EngineWindow()
{
}

EngineWindow::~EngineWindow()
{
}

void EngineWindow::OpenWindow()
{
	Register();
	Create();
}

void EngineWindow::Register()
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
	wcex.lpszClassName = "WindowClass";
	wcex.hIconSm = nullptr;

	ATOM A = RegisterClassExA(&wcex);
}

void EngineWindow::Create()
{
	hWnd = CreateWindowA("WindowClass", WindowTitle.c_str(), WS_OVERLAPPEDWINDOW,
		WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		DWORD errorCode = GetLastError();
		MessageBoxA(nullptr, "EngineWindow::Create() 실패", "Error", MB_OK);
		return;
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return;
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
			EngineCore::EngineUpdate();
		}
	}

	EngineCore::EngineRelease();
}
