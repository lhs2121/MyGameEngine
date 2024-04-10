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
	EngineObject* ParentOBJ = new EngineObject();
	EngineObject* ChildOBJ = new EngineObject();
	ChildOBJ->SetName("Ronaldo");
	EngineObject* ChildOBJ2 = new EngineObject();
	ChildOBJ2->SetName("Ronaldo2");
	EngineObject* ChildOBJ3 = new EngineObject();
	ChildOBJ3->SetName("Ronaldo3");
	EngineObject* ChildOBJ4 = new EngineObject();
	ChildOBJ4->SetName("Ronaldo4");
	EngineObject* ChildOBJ5 = new EngineObject();
	ChildOBJ5->SetName("Ronaldo5");

	ParentOBJ->PushChild(ChildOBJ);
	ParentOBJ->PushChild(ChildOBJ2);
	ParentOBJ->PushChild(ChildOBJ3);
	ParentOBJ->PushChild(ChildOBJ4);
	ParentOBJ->PushChild(ChildOBJ5);
	EngineObject* a = ParentOBJ->GetChild(5);

	ContentsCore CoreObject;
	EngineCore::EngineStart(hInstance, { 50, 50 }, { 1366,789 }, "Cilent", &CoreObject);
}

