#include "Pre.h"
#include "EngineCore.h"

EngineWindow EngineCore::MainWindow;
EngineDevice EngineCore::MainDevice;
EngineTime EngineCore::MainTime;
EngineLevel* EngineCore::CurLevel;
EngineObject* EngineCore::CoreObject = nullptr;

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

    MainDevice.Init();
    MainDevice.ResourceInit();

    CoreObject = _CoreObject;
    CoreObject->Start();

    MainTime.Init();
    MainTime.CountStart();


    MainWindow.MessageLoop();
}
void EngineCore::EngineUpdate()
{
    float Delta = MainTime.CountEnd();
    MainTime.CountStart();

    CurLevel->Update(Delta);

    MainDevice.Clear();

    CurLevel->Render();

    MainDevice.Present();

}



