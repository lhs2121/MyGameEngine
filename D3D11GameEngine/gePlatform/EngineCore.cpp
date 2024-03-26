#include "Pre.h"
#include "EngineCore.h"

EngineWindow EngineCore::MainWindow;

EngineCore::EngineCore()
{
}

EngineCore::~EngineCore()
{
}

void EngineCore::EngineStart(HINSTANCE inst)
{
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
    MainWindow.MessageLoop();
}

void EngineCore::EngineUpdate()
{

}

