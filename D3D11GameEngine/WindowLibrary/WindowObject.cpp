#include "pch.h"
#include "WindowObject.h"
#include <EngineLibrary/Interface.h>

CWindowObject* g_pWindowsObject = nullptr;

CWindowObject::CWindowObject()
{
	g_pWindowsObject = this;
}

void CWindowObject::Initialize(const char* szTitle, float posX, float posY, float width, float height, const HINSTANCE hInstance, IEngine* pEngine)
{
	m_szTitle = szTitle;
	m_posX = posX;
	m_posY = posY;
	m_width = width;
	m_height = height;
	m_hInstance = hInstance;
	m_pEngine = pEngine;

	WNDCLASSEXA wcex = { 0 };

	wcex.cbSize = sizeof(WNDCLASSEXA);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = "MainWindow";
	wcex.hIconSm = nullptr;

	ATOM A = RegisterClassExA(&wcex);

	SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	m_hWnd = CreateWindowA("MainWindow", szTitle, WS_OVERLAPPEDWINDOW,
		(int)m_posX, (int)m_posY, (int)m_width, (int)m_height, nullptr, nullptr, m_hInstance, nullptr);

	if (!m_hWnd)
		__debugbreak();

	m_dpi = GetDpiForWindow(m_hWnd);
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
}

LRESULT CALLBACK CWindowObject::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DPICHANGED:
	{
		g_pWindowsObject->m_dpi = GetDpiForWindow(g_pWindowsObject->m_hWnd);
		break;
	}
	case WM_SIZE:
	{
		g_pWindowsObject->m_width = LOWORD(lParam);
		g_pWindowsObject->m_height = HIWORD(lParam);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void CWindowObject::MessageLoop()
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
			m_pEngine->EngineUpdate();
		}
	}

	m_pEngine->EngineRelease();
}