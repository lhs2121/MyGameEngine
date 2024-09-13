#pragma once
#include "Windows.h"

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

namespace Window
{
	extern "C" MediaAPI void        Create(const char* _title, float4 _pos, float4 _size, const HINSTANCE _hInstance, IEngine* pEngine);

	extern "C" MediaAPI void        Delete();

	extern "C" MediaAPI void        MessageLoop();

	extern "C" MediaAPI const char* GetTitle();
	
	extern "C" MediaAPI	float       GetSizeX();

	extern "C" MediaAPI	float       GetSizeY();

	extern "C" MediaAPI	float       GetPosX();

	extern "C" MediaAPI	float       GetPosY();

	extern "C" MediaAPI	HINSTANCE   GethInst();

	extern "C" MediaAPI HWND*       GethWnd();
}


extern "C" MediaAPI void CreateEngineInput(IEngineInput** ppIEngineInput);
extern "C" MediaAPI void DeleteEngineInput(IEngineInput* pIEngineInput);
