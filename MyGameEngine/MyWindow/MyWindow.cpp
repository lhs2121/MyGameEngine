#include "MyWindow.h"


MyWindow* MyWindow::Inst;


void MyWindow::OpenWindow()
{
	MyRegisterClass();
	InitInstance();
}

void MyWindow::MyRegisterClass()
{
	WNDCLASSEXA wcex;

	wcex.cbSize = sizeof(WNDCLASSEXA);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = MyWindow::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInst;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = "MyGame";
	wcex.lpszClassName = "MyGameEngine";
	wcex.hIconSm = nullptr;

	RegisterClassExA(&wcex);
}

void MyWindow::InitInstance()
{
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// 창 크기 및 위치 설정
	int windowWidth = screenWidth;
	int windowHeight = screenHeight;
	int windowX = (screenWidth - windowWidth) / 2;
	int windowY = (screenHeight - windowHeight) / 2;


	hwnd = CreateWindowA("MyGameEngine", "MyGame", WS_OVERLAPPEDWINDOW | WS_SIZEBOX,
		windowX, windowY, 800, 600, nullptr, nullptr, hInst, nullptr);


	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	return;
}


LRESULT CALLBACK MyWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
void MyWindow::MessageLoop()
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
			
		}

		return;
	}
}
