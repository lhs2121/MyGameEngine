#include "Pre.h"
#include <geCore/EngineCore.h>

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
	wcex.hInstance = m_Hinst;
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
	m_Hwnd = CreateWindowA("Class000", m_WinTitle.c_str(), WS_OVERLAPPEDWINDOW,
		m_WinPos.ix(), m_WinPos.iy(), m_WinSize.ix(), m_WinSize.iy(), nullptr, nullptr, m_Hinst, nullptr);

	if (!m_Hwnd)
	{
		DWORD errorCode = GetLastError();
		MessageBoxA(nullptr, "EngineWindow::Create() 실패", "Error", MB_OK);
		return;
	}

	ShowWindow(m_Hwnd, SW_SHOW);
	UpdateWindow(m_Hwnd);

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
			EngineCore::CoreUpdate();
		}
	}
}
