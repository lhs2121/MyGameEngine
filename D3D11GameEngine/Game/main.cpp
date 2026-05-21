#include "pch.h"
#include <Windows.h>
#include <InputLibrary/Interface.h>
#include <BaseLibrary/Interface.h>
#include <RendererLibrary/Interface.h>
#include <WindowLibrary/Interface.h>
#include <Game/Interface.h>

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
