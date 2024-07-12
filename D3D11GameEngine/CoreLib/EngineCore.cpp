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

EngineLevel* EngineCore::CreateLevel(const char* _Name, EngineLevel* _NewLevel)
{
	_NewLevel->SetName(_Name);
	_NewLevel->Start();

	AllLevel.insert(std::make_pair(_Name, _NewLevel));
	return _NewLevel;
}

void EngineCore::ChangeLevel(const char* LevelName)
{
	if (AllLevel.end() != AllLevel.find(LevelName))
	{
		CurLevel = AllLevel[LevelName];
	}
}

void EngineCore::DeleteAllLevel()
{
	for (std::pair<const char*, EngineLevel*> pair : AllLevel)
	{
		EngineLevel* LevelPtr = pair.second;
		if (LevelPtr != nullptr)
		{
			delete LevelPtr;
			LevelPtr = nullptr;
		}
	}
	AllLevel.clear();
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
    
    CreateEngineInput(&MainInput);
    MainInput->InitAllKey();

    MainWindow->MessageLoop();

    MainTime.CountStart();
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
	CurLevel->ChildUpdate(Delta);
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



