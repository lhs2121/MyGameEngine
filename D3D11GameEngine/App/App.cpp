#pragma comment(lib, "geBase.lib")
#pragma comment(lib, "gePlatform.lib")
#pragma comment(lib, "geCore.lib")

#include <iostream>
#include <Windows.h>
#include <geCore\Pre.h>
#include <geCore\EngineCore.h>


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	EngineCore::EngineStart(hInstance);
}

