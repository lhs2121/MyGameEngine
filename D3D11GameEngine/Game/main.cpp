#include <Windows.h>
#include <common/declspec.h>
#include <common/commonPre.h>

#include <BaseLib/BaseAPI.h>
#include <EngineLib/Engine.h>
#include <GameLib/GameInitializer.h>

#pragma comment(lib,"EngineLib.lib")
#pragma comment(lib,"GameLib.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	//Debug::CrtSetBreakAlloc(406);
	Debug::CrtSetDbgFlag();

	GameInitializer gameInit;
	Engine mainEngine;
	mainEngine.EngineStart("GameEngine", 50, 50, 1366, 789, hInstance, &gameInit);
}