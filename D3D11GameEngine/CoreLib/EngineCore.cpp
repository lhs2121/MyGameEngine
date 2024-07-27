#include "Pre.h"
#include <BaseLib/BaseAPI.h>
#include <MediaLib/MediaAPI.h>
#include <D3D11Lib/D3D11API.h>
#include <GameLib/GameAPI.h>
#include "EngineCore.h"
#include "EngineLevel.h"
#include "Singleton.h"

EngineLevel* EngineCore::CreateLevel(const char* _Name, EngineLevel* _NewLevel)
{
	_NewLevel->SetName(_Name);
	_NewLevel->Awake();

	AllLevel.Add(_Name, _NewLevel);
	return _NewLevel;
}

void EngineCore::ChangeLevel(const char* _Name)
{
	CurLevel = (EngineLevel*)AllLevel.Get(_Name);
}

void EngineCore::DeleteAllLevel()
{
	//for (std::pair<EngineString, EngineLevel*> pair : AllLevel)
	//{
	//	EngineLevel* LevelPtr = pair.second;
	//	if (LevelPtr != nullptr)
	//	{
	//		delete LevelPtr;
	//		LevelPtr = nullptr;
	//	}
	//}
	//AllLevel.clear();
}

void EngineCore::EngineStart(const char* _WindowTitle, float4 _WindowPos, float4 _WindowSize, HINSTANCE _hInstance, IGameStarter* _Starter)
{
    CreateEngineWindow(&MainWindow);
    MainWindow->Init(_WindowTitle, _WindowPos, _WindowSize, _hInstance, this);

    CreateEngineD3DManager(&MainD3DManager);    

    MainDevice = MainD3DManager->CreateDevice();
    MainDevice->Init(MainWindow->GethWnd(), _WindowSize);
    MainDevice->ResourceInit(MainD3DManager);

	Starter = _Starter;
	Starter->GameStart();

	CreateEngineTime(&MainTime);
    MainTime->Init();
    
    CreateEngineInput(&MainInput);
    MainInput->Init();

    MainTime->CountStart();

    MainWindow->MessageLoop();
}

void EngineCore::EngineUpdate()
{
    if (CurLevel == nullptr)
    {
        return;
    }

    MainInput->SetAllKeyState();

    float Delta = MainTime->CountEnd();
    MainTime->CountStart();
	CurLevel->ChildUpdate(Delta);
    CurLevel->Update(Delta);

    MainDevice->Clear();

    CurLevel->Render();

    MainDevice->Present();
}

void EngineCore::EngineRelease()
{
	MainCore->DeleteAllLevel();
	DeleteEngineTime(MainTime);
	DeleteEngineInput(MainInput);
	DeleteEngineD3DManager(MainD3DManager);
    DeleteEngineWindow(MainWindow);
}



