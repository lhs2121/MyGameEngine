#pragma once
#ifdef EngineMediaLib
#define EngineMediaAPI __declspec(dllexport)
#else
#define EngineMediaAPI __declspec(dllimport)
#endif

class float4;
class EngineCore;
struct ICore;
struct IEngineInput
{
	virtual void CreateKey(int KeyCode) = 0;

	virtual void InitAllKey() = 0;
	virtual void DeleteAllKey() = 0;

	virtual void SetAllKeyState() = 0;

	virtual bool IsDown(int KeyCode) = 0;
	virtual bool IsPress(int KeyCode) = 0;
	virtual bool IsUp(int KeyCode) = 0;
	virtual bool IsFree(int KeyCode) = 0;
};

struct IEngineWindow
{
	virtual void Init(const char* _WindowTile, float4 _WindowPos, float4 _WindowSize, const HINSTANCE _hInst, ICore* _Core) = 0;
	virtual void MessageLoop() = 0;

	virtual const char* GetWindowTitle() = 0;

	virtual	float4 GetWindowSize() const = 0;
	virtual	float4 GetWindowPos() const = 0;
	virtual	HINSTANCE GethInst() const = 0;
	virtual HWND* GethWnd() = 0;
};

extern "C" EngineMediaAPI void CreateEngineInput(IEngineInput** ppIEngineInput);
extern "C" EngineMediaAPI void DeleteEngineInput(IEngineInput* pIEngineInput);

extern "C" EngineMediaAPI void CreateEngineWindow(IEngineWindow** ppIEngineWindow);
extern "C" EngineMediaAPI void DeleteEngineWindow(IEngineWindow* pIEngineWindow);