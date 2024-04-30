#include "Pre.h"
#include "EngineCore.h"

EngineWindow EngineCore::MainWindow;
EngineDevice EngineCore::MainDevice;
EngineTime EngineCore::MainTime;
EngineLevel* EngineCore::CurLevel;
EngineObject* EngineCore::CoreObject = nullptr;
IEngineInput* EngineCore::InputInterface = nullptr;

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

    CreateInput(&InputInterface);
    InputInterface->InitAllKey();
    //EngineInput::InitAllKey();

    MainWindow.MessageLoop();
}
void EngineCore::EngineUpdate()
{
    if (CurLevel == nullptr)
    {
        return;
    }

    InputInterface->SetAllKeyState();
    //EngineInput::SetAllKeyState();

    float Delta = MainTime.CountEnd();
    MainTime.CountStart();
    CurLevel->ActorUpdate(Delta);
    CurLevel->Update(Delta);

    MainDevice.Clear();

    CurLevel->Render();

    MainDevice.Present();
}

void EngineCore::EngineRelease()
{
    EngineCore::DeleteAllLevel();
    InputInterface->DeleteAllKey();
    if (InputInterface != nullptr)
    {
        delete InputInterface;
        InputInterface = nullptr;
    }
    EngineVertexBuffer::DeleteAllResource();
    EngineIndexBuffer::DeleteAllResource();
    EngineInputLayout::DeleteAllResource();
    EngineVertexShader::DeleteAllResource();
    EngineRasterizer::DeleteAllResource();
    EnginePixelShader::DeleteAllResource();
    EngineDepthStencil::DeleteAllResource();
}



