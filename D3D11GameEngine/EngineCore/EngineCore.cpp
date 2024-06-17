#include "Pre.h"
#include "EngineCore.h"

EngineWindow EngineCore::MainWindow;
IEngineDevice* EngineCore::MainDevice = nullptr;
EngineTime EngineCore::MainTime;
EngineLevel* EngineCore::CurLevel;
EngineObject* EngineCore::CoreObject = nullptr;
IEngineInput* EngineCore::MainInput = nullptr;
IEngineD3DManager* EngineCore::MainD3DManager = nullptr;

std::map<const char*, EngineLevel*> EngineCore::AllLevel;

EngineCore::EngineCore()
{
}

EngineCore::~EngineCore()
{
}

void EngineCore::EngineStart(HINSTANCE _hInstance, float4 _WindowPos, float4 _WindowSize, const char* _WindowTitle, EngineObject* _CoreObject)
{
    MainWindow.SetWinPos(_WindowPos);
    MainWindow.SetWinSize(_WindowSize);
    MainWindow.SetWinTitle(_WindowTitle);
    MainWindow.SetHinstance(_hInstance);
    MainWindow.OpenWindow();

    CreateEngineD3DManager(&MainD3DManager);    
    MainDevice = MainD3DManager->CreateDevice();
    MainDevice->Init(MainWindow.GetHwnd(), _WindowSize);
    MainDevice->ResourceInit(MainD3DManager);

    CoreObject = _CoreObject;
    CoreObject->Start();

    MainTime.Init();
    MainTime.CountStart();
    
    CreateInput(&MainInput);
    MainInput->InitAllKey();

    MainWindow.MessageLoop();
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
}



