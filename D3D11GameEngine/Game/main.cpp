#include <Windows.h>
#include <common/declspec.h>
#include <common/commonPre.h>

#include <BaseLib/EngineDebug.h>
#include <MediaLib/MediaAPI.h>
#include <ResourceLib/ResourceAPI.h>
#include <EngineLib/Engine.h>
#include <GameLib/GameSceneManager.h>

#pragma comment(lib,"MediaLib.lib")
#pragma comment(lib,"EngineLib.lib")
#pragma comment(lib,"GameLib.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//EngineDebug::CrtSetBreakAlloc(761);
	EngineDebug::CrtSetDbgFlag();

	GameSceneManager sceneManager;
	Engine mainEngine;
	mainEngine.EngineStart("GameEngine", 50, 50, 1366, 789, hInstance, &sceneManager);
}