#pragma once
#include "Windows.h"

struct IEngine;
namespace Input
{
	MediaAPI void        Create();

	MediaAPI void        Delete();

	extern "C" MediaAPI void        UpdateKeyStates();

	extern "C" MediaAPI bool        IsDown(int _key, void* pUser);

	extern "C" MediaAPI bool        IsPress(int _key, void* pUser);

	extern "C" MediaAPI bool        IsUp(int _key, void* pUser);

	extern "C" MediaAPI bool        IsFree(int _key, void* pUser);

	extern "C" MediaAPI void        AddUser(void* pUser);
}

namespace Window
{
	MediaAPI void        Create(const char* _title, float4 _pos, float4 _size, const HINSTANCE _hInstance, IEngine* pEngine);

	MediaAPI void        Delete();

	extern "C" MediaAPI void        MessageLoop();

	extern "C" MediaAPI const char* GetTitle();

	extern "C" MediaAPI	float       GetSizeX();

	extern "C" MediaAPI	float       GetSizeY();

	extern "C" MediaAPI	float       GetPosX();

	extern "C" MediaAPI	float       GetPosY();

	extern "C" MediaAPI	HINSTANCE   GethInst();

	extern "C" MediaAPI HWND*       GethWnd();
}