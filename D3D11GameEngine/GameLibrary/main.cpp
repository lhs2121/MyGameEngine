#include "pch.h"
#include <Windows.h>
#include <InputLibrary/Interface.h>
#include <BaseLibrary/Interface.h>
#include <RendererLibrary/Interface.h>
#include <WindowLibrary/Interface.h>
#include <GameLibrary/Interface.h>

#pragma comment(lib, "BaseLibrary.lib")
#pragma comment(lib, "InputLibrary.lib")
#pragma comment(lib, "WindowLibrary.lib")
#pragma comment(lib, "RendererLibrary.lib")
#pragma comment(lib, "CollisionLibrary.lib")
#pragma comment(lib, "EngineLibrary.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//Debug::CrtSetBreakAlloc(406);
	Debug::CrtSetDbgFlag();

	GameStater gameInitializer;
	Engine engine;
	engine.EngineStart("LegoEngine <DX11>", 50, 50, 1366, 789, hInstance, &gameInitializer);
}