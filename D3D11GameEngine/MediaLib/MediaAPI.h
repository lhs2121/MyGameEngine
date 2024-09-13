#pragma once
#include "Windows.h"

struct IEngine;

namespace Input
{
	extern "C" MediaAPI void        CreateInput();

	extern "C" MediaAPI void        DeleteInput();

	extern "C" MediaAPI void        UpdateKeyStates();

	extern "C" MediaAPI bool        IsDown(int _key, void* pUser);

	extern "C" MediaAPI bool        IsPress(int _key, void* pUser);

	extern "C" MediaAPI bool        IsUp(int _key, void* pUser);

	extern "C" MediaAPI bool        IsFree(int _key, void* pUser);

	extern "C" MediaAPI void        AddUser(void* pUser);
}

namespace Window
{
	extern "C" MediaAPI void        CreateWindowInst(const char* _title, float4 _pos, float4 _size, const HINSTANCE _hInstance, IEngine* pEngine);

	extern "C" MediaAPI void        DeleteWindowInst();

	extern "C" MediaAPI void        MessageLoop();

	extern "C" MediaAPI const char* GetTitle();

	extern "C" MediaAPI	float       GetSizeX();

	extern "C" MediaAPI	float       GetSizeY();

	extern "C" MediaAPI	float       GetPosX();

	extern "C" MediaAPI	float       GetPosY();

	extern "C" MediaAPI	HINSTANCE   GethInst();

	extern "C" MediaAPI HWND*       GethWnd();
}