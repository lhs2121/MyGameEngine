#pragma comment(lib, "EngineBase.lib")
#pragma comment(lib, "EngineWindow.lib")
#pragma comment(lib, "EngineCore.lib")
#pragma comment(lib, "EngineContents.lib")

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "D3DCompiler.lib")

#pragma comment(lib, "EngineInputLib.lib")
#pragma comment(lib, "EngineD3DResourceLib.lib")

#include <iostream>
#include <Windows.h>
#include <EngineContents\Pre.h>
#include <EngineContents\ContentsCore.h>


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//EngineDebug::CrtSetBreakAlloc(243);
	EngineDebug::CrtSetDbgFlag();
	ContentsCore CoreObject;
	EngineCore::EngineStart(hInstance, { 50, 50 }, { 1366,789 }, "Cilent", &CoreObject);
}

