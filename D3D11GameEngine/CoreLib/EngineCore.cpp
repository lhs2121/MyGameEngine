#include "Pre.h"
#include "EngineCore.h"
#include "EngineLevel.h"

EngineCore::EngineCore()
{
}

EngineCore::~EngineCore()
{
}

ILevel* EngineCore::CreateLevel(const char* _Name, ILevel* _NewLevel)
{
	_NewLevel = new EngineLevel();
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

void EngineCore::EngineStart(const char* _WindowTitle, float4 _WindowPos, float4 _WindowSize, HINSTANCE _hInstance, IObject* _CoreObject)
{
    CreateEngineWindow(&MainWindow);
    MainWindow->Init(_WindowTitle, _WindowPos, _WindowSize, _hInstance, this);

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



