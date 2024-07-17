#include <Windows.h>
#include <CoreLib/CoreAPI.h>
#include <BaseLib/EngineMath.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	ICore* Core;
	CreateEngineCore(&Core);
	return 0;
}