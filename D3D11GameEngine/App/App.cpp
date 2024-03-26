#pragma comment(lib, "geBase.lib")
#pragma comment(lib, "gePlatform.lib")

#include <iostream>
#include <Windows.h>
#include <memory>
#include <gePlatform\Pre.h>
#include <gePlatform\EngineCore.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	EngineCore::EngineStart(hInstance);
}

