#include "pch.h"
#include <Windows.h>
#include <BaseLibrary/Interface.h>
#include <EngineLibrary/Interface.h>
#pragma comment(lib, "BaseLibrary.lib")
#pragma comment(lib, "EngineLibrary.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//Debug::CrtSetBreakAlloc(406);
	Debug::CrtSetDbgFlag();

	IEngine* pEngine;
	CreateEngine(&pEngine);
	pEngine->EngineStart("LegoEngine <DX11>", 50, 50, 1366, 789, hInstance);
}