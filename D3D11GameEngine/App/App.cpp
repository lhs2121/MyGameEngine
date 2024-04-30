#pragma comment(lib, "EngineBase.lib")
#pragma comment(lib, "EngineWindow.lib")
#pragma comment(lib, "EngineCore.lib")
#pragma comment(lib, "EngineContents.lib")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "D3DCompiler")
#pragma comment(lib, "Input.lib")

#include <iostream>
#include <Windows.h>
#include <EngineContents\Pre.h>
#include <EngineContents\ContentsCore.h>


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//EngineDebug::CrtSetBreakAlloc(488);
	EngineDebug::CrtSetDbgFlag();
	ContentsCore CoreObject;
	EngineCore::EngineStart(hInstance, { 50, 50 }, { 1920,1080 }, "Cilent", &CoreObject);
}

