#include "Pre.h"
#include "EngineCore.h"

EngineWindow EngineCore::MainWindow;
IEngineDevice* EngineCore::MainDevice = nullptr;
EngineTime EngineCore::MainTime;
EngineLevel* EngineCore::CurLevel;
EngineObject* EngineCore::CoreObject = nullptr;
IEngineInput* EngineCore::MainInput = nullptr;
IEngineD3DResourceManager* EngineCore::MainResourceManager = nullptr;

std::map<std::string, EngineLevel*> EngineCore::AllLevel;

EngineCore::EngineCore()
{
}

EngineCore::~EngineCore()
{
}

void EngineCore::EngineStart(HINSTANCE _hInstance, float4 _WindowPos, float4 _WindowSize, std::string _WindowTitle, EngineObject* _CoreObject)
{
    MainWindow.SetWinPos(_WindowPos);
    MainWindow.SetWinSize(_WindowSize);
    MainWindow.SetWinTitle(_WindowTitle);
    MainWindow.SetHinstance(_hInstance);
    MainWindow.OpenWindow();

    CreateD3DResourceManger(&MainResourceManager);    
    MainDevice = MainResourceManager->CreateDevice();
    MainDevice->Init(MainWindow.GetHwnd(), _WindowSize);
    MainDevice->ResourceInit(MainResourceManager);

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

	if (MainResourceManager != nullptr)
	{
        MainResourceManager->Release();
		delete MainResourceManager;
		MainResourceManager = nullptr;
	}

	if (MainDevice != nullptr)
	{
        MainDevice->Release();
		delete MainDevice;
		MainDevice = nullptr;
	}
}



