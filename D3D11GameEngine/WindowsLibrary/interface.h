#pragma once
#include "Windows.h"

#ifdef WINDOWSLIBRARY_EXPORTS
#define WindowsLibraryAPI __declspec(dllexport)
#else
#define WindowsLibraryAPI __declspec(dllimport)
#endif // WINDOWSLIBRARY_EXPORTS


struct IEngine;

struct IWindowObject
{
	virtual void Initialize(const char* szTitle, float posX, float posY, float width, float height, const HINSTANCE hInstance, IEngine* pEngine) = 0;

    virtual void MessageLoop() = 0;

	virtual const char* GetTitle() = 0;

	virtual float GetWidth() = 0;

	virtual float GetHeight() = 0;

	virtual float GetPosX() = 0;

	virtual float GetPosY() = 0;

	virtual HINSTANCE GetHINSTANCE() = 0;

	virtual HWND* GetHWND() = 0;

};

extern "C" WindowsLibraryAPI void CreateWindowObject(IWindowObject** ppWindowObject);

extern "C" WindowsLibraryAPI void DeleteWindowObject(IWindowObject* pWindowObject);
