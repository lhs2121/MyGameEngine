#include <Windows.h>
#include <CoreLib\ICoreLib.h>
#include <EngineBaseLib\EngineBaseLib\EngineMath.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	ICore* Core;
	CreateEngineCore(&Core, "Game", { 50,50 }, { 1366,789 }, hInstance, );
	return 0;
}