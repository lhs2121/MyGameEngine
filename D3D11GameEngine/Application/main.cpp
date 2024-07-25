#include <Windows.h>
#include <BaseLib/BaseAPI.h>
#include <CoreLib/CoreAPI.h>
#include <GameLib/GameAPI.h>

#pragma comment(lib,"BaseLib.lib")
#pragma comment(lib,"CoreLib.lib")
#pragma comment(lib,"GameLib.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	ICore* Core;
	IGameStarter* Starter;
	CreateGameStarter(&Starter);
	CreateEngineCore(&Core);
	Core->EngineStart("GameEngine", { 50,50 }, { 1366,789 }, hInstance, Starter);
}