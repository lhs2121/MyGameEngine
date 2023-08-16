#pragma comment(lib, "MyWindow")

#include <MyWindow/MyWindow.h>


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	new MyWindow();
	MyWindow::Inst->SetHinstance(hInstance);
	MyWindow::Inst->OpenWindow();
	MyWindow::Inst->MessageLoop();
}

