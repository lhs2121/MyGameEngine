#pragma once
struct IEngineWindow;
struct IEngineInput;
struct IEngineDevice;
struct IEngineD3DManager;
class EngineCore;

extern CoreAPI EngineCore* MainCore;
extern CoreAPI EngineTime* MainTime;
extern CoreAPI IEngineWindow* MainWindow;
extern CoreAPI IEngineInput* MainInput;
extern CoreAPI IEngineDevice* MainDevice;
extern CoreAPI IEngineD3DManager* MainD3DManager;

