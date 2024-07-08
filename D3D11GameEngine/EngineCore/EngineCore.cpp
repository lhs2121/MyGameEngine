#include "Pre.h"
#include "EngineCore.h"
#include "EngineLevel.h"

IEngineWindow* EngineCore::MainWindow = nullptr;
IEngineInput* EngineCore::MainInput = nullptr;

IEngineDevice* EngineCore::MainDevice = nullptr;
IEngineD3DManager* EngineCore::MainD3DManager = nullptr;

EngineTime EngineCore::MainTime;

EngineLevel* EngineCore::CurLevel;
EngineObject* EngineCore::CoreObject = nullptr;

std::map<const char*, EngineLevel*> EngineCore::AllLevel;

EngineCore::EngineCore()
{
}

EngineCore::~EngineCore()
{
}

void EngineCore::EngineStart(const char* _WindowTitle, float4 _WindowPos, float4 _WindowSize, HINSTANCE _hInstance, EngineObject* _CoreObject)
{
    CreateEngineWindow(&MainWindow);
    MainWindow->Init(_WindowTitle, _WindowPos, _WindowSize, _hInstance, EngineUpdate, EngineRelease);

    CreateEngineD3DManager(&MainD3DManager);    

    MainDevice = MainD3DManager->CreateDevice();
    MainDevice->Init(MainWindow->GethWnd(), _WindowSize);
    MainDevice->ResourceInit(MainD3DManager);

    CoreObject = _CoreObject;
    CoreObject->Start();

    MainTime.Init();
    MainTime.CountStart();
    
    CreateEngineInput(&MainInput);
    MainInput->InitAllKey();

    MainWindow->MessageLoop();
}
void EngineCore::EngineUpdate()
{
    if (CurLevel == nullptr)
    {
        return;
    }

    MainInput->SetAllKeyState();

    float Delta = MainTime.CountEnd();
    MainTime.CountStart();  
    CurLevel->ActorUpdate(Delta);
    CurLevel->Update(Delta);

    MainDevice->Clear();

    CurLevel->Render();

    MainDevice->Present();
}

void EngineCore::EngineRelease()
{
	EngineCore::DeleteAllLevel();

	if (MainInput != nullptr)
	{
	    MainInput->DeleteAllKey();
		delete MainInput;
		MainInput = nullptr;
	}

	if (MainD3DManager != nullptr)
	{
        MainD3DManager->Release();
		delete MainD3DManager;
		MainD3DManager = nullptr;
	}

	if (MainDevice != nullptr)
	{
        MainDevice->Release();
		delete MainDevice;
		MainDevice = nullptr;
	}

    DeleteEngineWindow(MainWindow);
}



