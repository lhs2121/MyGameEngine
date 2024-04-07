#include "Pre.h"
#include "EngineCore.h"
#include <geContents\ContentsCore.h>

EngineRenderer EngineCore::TestRenderer;
EngineWindow EngineCore::MainWindow;
EngineDevice EngineCore::MainDevice;
ContentsCore* EngineCore::CoreObj = nullptr;

EngineCore::EngineCore()
{
}

EngineCore::~EngineCore()
{
}

void EngineCore::EngineStart(HINSTANCE inst)
{
    CoreObj->Start();

    std::string Title;

#ifdef _DEBUG
    Title = "D3D11_Clinet_Debug";
#else
    Title = "D3D11_Clinet_Release";
#endif

#ifdef _WIN64
    Title += "_x64";
#else
    Title += "_x86";
#endif

    MainWindow.SetWinPos({ 50,50 });
    MainWindow.SetWinSize({ 1366,789 });
    MainWindow.SetWinTitle(Title);
    MainWindow.SetHinstance(inst);
    MainWindow.OpenWindow();

    EngineCore::CoreStart();

    MainWindow.MessageLoop();
}

void EngineCore::CoreStart()
{
    MainDevice.Init();
    MainDevice.ResourceInit();
    TestRenderer.Start();
}

void EngineCore::CoreUpdate()
{
    MainDevice.Clear();
    TestRenderer.Render();
    MainDevice.Present();
}

void EngineCore::CoreRelease()
{

}

