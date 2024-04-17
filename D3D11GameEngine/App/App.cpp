#pragma comment(lib, "EngineBase.lib")
#pragma comment(lib, "EngineWindow.lib")
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
	float4 Degree = { 90,90,90 };
	float4x4 RotMatX;
	float4x4 RotMatY;
	float4x4 RotMatZ;
	float DegreeToRadian = PI / 180;
	RotMatY.RotationY(90* DegreeToRadian);
	RotMatZ.RotationZ(90* DegreeToRadian);
	RotMatX.RotationX(90* DegreeToRadian);
	float4x4 rotmat = RotMatZ * RotMatY * RotMatX;
	float4 Position = { 1,0,0 };
	float4 RotationPos = Position * RotMatZ;
	float4 RotationPos2 = RotationPos * RotMatY;
	float4 RotationPos3 = RotationPos2 * RotMatX;
	//_CrtSetBreakAlloc(402);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	ContentsCore CoreObject;
	EngineCore::EngineStart(hInstance, { 50, 50 }, { 500,500 }, "Cilent", &CoreObject);
}

