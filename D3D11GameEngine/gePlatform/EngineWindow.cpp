#include "Pre.h"
#include "EngineCore.h"
#include "EngineWindow.h"

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
	wcex.hInstance = HInst;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = "Class000";
	wcex.hIconSm = nullptr;

	ATOM A = RegisterClassExA(&wcex);
}

void EngineWindow::Create()
{
	Hwnd = CreateWindowA("Class000", WinTitle.c_str(), WS_OVERLAPPEDWINDOW,
		WinPos.X, WinPos.Y, WinSize.X, WinSize.Y, nullptr, nullptr, HInst, nullptr);

	if (!Hwnd)
	{
		DWORD errorCode = GetLastError();
		MessageBoxA(nullptr, "EngineWindow::Create() 실패", "Error", MB_OK);
		return;
	}

	ShowWindow(Hwnd, SW_SHOW);
	UpdateWindow(Hwnd);

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
}
