#pragma once
#include "Windows.h"

#ifdef WINDOWSLIBRARY_EXPORTS
#define WindowsAPI __declspec(dllexport)
#else
#define WindowAPI __declspec(dllimport)
#endif // WINDOWSLIBRARY_EXPORTS

struct IEngine;
extern "C" WindowsAPI (const char* szTitle, float posX, float posY, float sizeX, float sizeY, const HINSTANCE hInstance, IEngine* pEngine)
struct IWindow
{

};
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