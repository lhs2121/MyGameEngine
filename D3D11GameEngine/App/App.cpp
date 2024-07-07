#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "D3DCompiler.lib")

#pragma comment(lib, "EngineBaseLib.lib")
#pragma comment(lib, "EngineMediaLib.lib")
#pragma comment(lib, "EngineD3DResourceLib.lib")
#pragma comment(lib, "EngineCore.lib")
#pragma comment(lib, "EngineContents.lib")

#include <Windows.h>
#include <EngineCore\EngineCore.h>
#include <EngineContents\ContentsCore.h>
#include <EngineBaseLib\EngineBaseLib\EngineBaseInterface.h>

const float4 HD = { 1280,720 };
const float4 FWXGA = { 1366,768 };
const float4 FHD = { 1920,1080 };
const float4 QHD = { 2560,1440 };
const float4 WindowPos = { 50,50 };
ContentsCore CoreObject;

const char* func1(const char* string)
{
	return string;
}
int func2(int a)
{
	a++;
	a--;
	a++;
	a--;
	a++;
	a--;
	a++;
	a--;
	a++;
	a--;
	a++;
	a--;
	a++;
	a--;
	a++;
	a--;
	return a;
}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	double time = EngineDebug::CalculateTime(std::bind(func1,"asd"), 99999,"Func1");
	double time2 = EngineDebug::CalculateTime(std::bind(func2,2), 99999, "Func2");
	//EngineDebug::CrtSetBreakAlloc(249);
	EngineDebug::CrtSetDbgFlag();
	EngineCore::EngineStart("D3D11GameEngine", WindowPos, FWXGA, hInstance, &CoreObject);
	EngineString::DeleteAllStringPool();
}

