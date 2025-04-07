#pragma once
#include <DirectXMath.h>
#include "d3d11.h"
#include "Windows.h"

#ifdef RENDERERLIBRARY_EXPORTS
#define RENDERERLIBRARY_API __declspec(dllexport)
#else
#define RENDERERLIBRARY_API __declspec(dllimport)
#endif 

using namespace DirectX;

struct IMeshObject
{
	virtual void SetWireFrame() = 0;
	virtual void SetSolid() = 0;
};

struct IRenderer
{
	virtual void Initialize(UINT winSizeX, UINT winSizeY, HWND& hwnd) = 0;

	virtual void StartRender() = 0;
	virtual void EndRender() = 0;

	virtual IMeshObject* CreateMeshObject() = 0;
};

extern "C" RENDERERLIBRARY_API void CreateRenderer(IRenderer** ppRenderer);
extern "C" RENDERERLIBRARY_API void DeleteRenderer(IRenderer* pRenderer);