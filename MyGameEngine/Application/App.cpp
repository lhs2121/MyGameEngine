#pragma comment(lib, "MyWindow.lib")
#pragma comment(lib, "MyBase.lib")

#include <MyWindow/MyWindow.h>
#include <MyWindow/MyRenderer.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	new MyWindow();
	MyWindow::Inst->SetHinstance(hInstance);
	MyWindow::Inst->OpenWindow();

	new MyRenderer();
	MyRenderer::Inst->Init();
	MyRenderer::Inst->Render();

	MyWindow::Inst->MessageLoop();
}

