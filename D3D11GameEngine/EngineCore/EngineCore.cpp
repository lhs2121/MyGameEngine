#include "Pre.h"
#include "EngineCore.h"

EngineRenderer EngineCore::TestRenderer;
EngineWindow EngineCore::MainWindow;
EngineDevice EngineCore::MainDevice;
EngineTime EngineCore::MainTimer;
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

    CoreObject = _CoreObject;
    CoreObject->Start();

    MainDevice.Init();
    MainDevice.ResourceInit();

    MainTimer.Init();
    MainTimer.CountStart();

    TestRenderer.Start();

    MainWindow.MessageLoop();
}
void EngineCore::EngineUpdate()
{
    float Delta = MainTimer.CountEnd();
    MainTimer.CountStart();

    CurLevel->Update(Delta);

    MainDevice.Clear();
    TestRenderer.Render();
    MainDevice.Present();

}



