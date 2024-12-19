#pragma once
#include "Windows.h"

#ifdef WINDOWLIBRARY_EXPORTS
#define WindowLibraryAPI __declspec(dllexport)
#else
#define WindowLibraryAPI __declspec(dllimport)
#endif 

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

extern "C" WindowLibraryAPI void CreateWindowObject(IWindowObject** ppWindowObject);

extern "C" WindowLibraryAPI void DeleteWindowObject(IWindowObject* pWindowObject);
