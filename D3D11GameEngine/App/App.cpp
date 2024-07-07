#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "D3DCompiler.lib")

#pragma comment(lib, "EngineBaseLib.lib")
#pragma comment(lib, "EngineMediaLib.lib")
#pragma comment(lib, "EngineD3DResourceLib.lib")
#pragma comment(lib, "EngineCore.lib")
#pragma comment(lib, "EngineContents.lib")

#include <iostream>
#include <Windows.h>
#include <EngineContents\Pre.h>
#include <EngineContents\ContentsCore.h>


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//EngineDebug::CrtSetBreakAlloc(249);
	EngineDebug::CrtSetDbgFlag();
	ContentsCore CoreObject;
	EngineCore::EngineStart("Cilent", { 50, 50 }, { 1366,789 }, hInstance, &CoreObject);
	EngineString::DeleteAllStringPool();
}

