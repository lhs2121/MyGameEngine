#pragma once

struct float4;
struct IEngine;
struct IEngineInput
{
	virtual void CreateKey(int KeyCode) = 0;

	virtual void Init() = 0;
	virtual void UpdateKeyStates() = 0;

	virtual bool IsDown(int KeyCode, void* _UserPtr) = 0;
	virtual bool IsPress(int KeyCode, void* _UserPtr) = 0;
	virtual bool IsUp(int KeyCode, void* _UserPtr) = 0;
	virtual bool IsFree(int KeyCode, void* _UserPtr) = 0;
	virtual void AddUser(void* _UserPtr) = 0;
};

struct IEngineWindow
{
	virtual void Init(const char* _WindowTile, float4 _WindowPos, float4 _WindowSize, const HINSTANCE _hInst, IEngine* _pMainEngine) = 0;
	virtual void MessageLoop() = 0;

	virtual const char* GetWindowTitle() = 0;

	virtual	float4 GetWindowSize() const = 0;
	virtual	float4 GetWindowPos() const = 0;
	virtual	HINSTANCE GethInst() const = 0;
	virtual HWND* GethWnd() = 0;
};

extern "C" MediaAPI void CreateEngineInput(IEngineInput** ppIEngineInput);
extern "C" MediaAPI void DeleteEngineInput(IEngineInput* pIEngineInput);

extern "C" MediaAPI void CreateEngineWindow(IEngineWindow** ppIEngineWindow);
extern "C" MediaAPI void DeleteEngineWindow(IEngineWindow* pIEngineWindow);