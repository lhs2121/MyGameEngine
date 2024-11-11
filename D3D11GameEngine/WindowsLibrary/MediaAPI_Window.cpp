#include "Pre.h"
#include "MediaAPI.h"
#include "EngineWindow.h"

void Window::Create(const char* _title, float4 _pos, float4 _size, const HINSTANCE _hInstance, IEngine* pEngine)
{
	if (EngineWindow::mainWindow != nullptr)
	{
		Debug::MsgBoxAssert("이미 만들어진 윈도우가 있습니다.");
	}

	EngineWindow* window = new EngineWindow();
	window->Init(_title, _pos, _size, _hInstance, pEngine);
}

void Window::Delete()
{
	delete EngineWindow::mainWindow;
}

void Window::MessageLoop()
{
	EngineWindow::mainWindow->MessageLoop();
}

const char* Window::GetTitle()
{
	return EngineWindow::mainWindow->title;
}

float Window::GetSizeX()
{
	return EngineWindow::mainWindow->size.x;
}
float Window::GetSizeY()
{
	return EngineWindow::mainWindow->size.y;
}
float Window::GetPosX()
{
	return EngineWindow::mainWindow->pos.x;
}

float Window::GetPosY()
{
	return EngineWindow::mainWindow->pos.y;
}

HINSTANCE Window::GethInst() 
{
	return EngineWindow::mainWindow->hInstance;
}

HWND* Window::GethWnd()
{
	return &EngineWindow::mainWindow->hWnd;
}
