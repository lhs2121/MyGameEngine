#include <Windows.h>
#include <common/declspec.h>
#include <common/commonPre.h>
#include <BaseLib/EngineDebug.h>
#include <BaseLib/EngineMath.h> 
#include <D3D11Lib/D3D11API.h>
#include <MediaLib/MediaAPI.h>
#include <CoreLib/CoreAPI.h>
#include <GameLib/GameAPI.h>

#include <CoreLib/EngineCore.h>
#pragma comment(lib,"BaseLib.lib")
#pragma comment(lib,"CoreLib.lib")
#pragma comment(lib,"GameLib.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//EngineDebug::CrtSetBreakAlloc(385);
	EngineDebug::CrtSetDbgFlag();
	IGameStarter* Starter;
	CreateGameStarter(&Starter);

	EngineCore MainCore;
	MainCore.EngineStart("GameEngine", { 50,50 }, { 1366,789 }, hInstance, Starter);

	DeleteGameStarter(Starter);
}