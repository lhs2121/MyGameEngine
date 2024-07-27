#include "Pre.h"
#include "Singleton.h"

EngineCore* MainCore = nullptr;
IEngineTime* MainTime = nullptr;
IEngineWindow* MainWindow = nullptr;
IEngineInput* MainInput = nullptr;
IEngineDevice* MainDevice = nullptr;
IEngineD3DManager* MainD3DManager = nullptr;