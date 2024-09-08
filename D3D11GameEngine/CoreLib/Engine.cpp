#include "Pre.h"
#include <BaseLib/BaseAPI.h>
#include <MediaLib/MediaAPI.h>
#include <D3D11Lib/D3D11API.h>
#include <GameLib/GameAPI.h>
#include "Engine.h"
#include "Level.h"

Level* Engine::CreateLevel(const char* _Name, Level* _NewLevel)
{
    _NewLevel->Input = MainInput;
    _NewLevel->Window = MainWindow;
    _NewLevel->Device = MainDevice;
    _NewLevel->ResManager = MainResManager;
	_NewLevel->SetName(_Name);
    _NewLevel->CreateCamera();
	_NewLevel->Awake();

	AllLevel.Add(_Name, _NewLevel);
	return _NewLevel;
}

void Engine::ChangeLevel(const char* _Name)
{
	CurLevel = (Level*)AllLevel.Get(_Name);
}

void Engine::DeleteAllLevel()
{
	AllLevel.GoFirst();
	UINT Count = AllLevel.Count();

	for (UINT i = 0; i < Count; i++)
	{
		Level* CurLevel = (Level*)AllLevel.GetCurItem();
		delete CurLevel;
		AllLevel.GoNext();
	}
}

void Engine::EngineStart(const char* _WindowTitle, float4 _WindowPos, float4 _WindowSize, HINSTANCE _hInstance, IGameStarter* _Starter)
{
    CreateEngineWindow(&MainWindow);
    MainWindow->Init(_WindowTitle, _WindowPos, _WindowSize, _hInstance, this);

    CreateResManager(&MainResManager);
    MainResManager->CreateDevice(&MainDevice);

    MainDevice->Init(MainWindow->GethWnd(), _WindowSize);
    MainDevice->InitMesh(MainResManager);
    MainDevice->InitMaterial(MainResManager);

	CreateEngineTime(&MainTime);
    MainTime->Init();
    
    CreateEngineInput(&MainInput);
    MainInput->Init();

    Starter = _Starter;
    Starter->GameStart(this);

    MainTime->CountStart();

    MainWindow->MessageLoop();
}

void Engine::EngineUpdate()
{
    if (CurLevel == nullptr)
    {
        return;
    }

    MainInput->UpdateKeyStates();

    float Delta = MainTime->CountEnd();
    MainTime->CountStart();
	CurLevel->ChildUpdate(Delta);
    CurLevel->Update(Delta);

    MainDevice->Clear();

    CurLevel->Render();

    MainDevice->Present();
}

void Engine::EngineRelease()
{
	DeleteAllLevel();
	DeleteEngineTime(MainTime);
	DeleteEngineInput(MainInput);
	DeleteResManager(MainResManager);
    DeleteEngineWindow(MainWindow);
    EngineString::DeleteAllStringPool();
}



