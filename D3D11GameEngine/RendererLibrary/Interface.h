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

struct ISpriteObject
{
	virtual void UpdateAnimation(float deltaTime) = 0;
};

struct IRenderer
{
	virtual void Initialize(UINT winSizeX, UINT winSizeY, HWND& hwnd) = 0;

	virtual void StartRender() = 0;
	virtual void EndRender() = 0;

	virtual void LoadTexture(const WCHAR* textureFile) = 0;
	virtual ISpriteObject* CreateSpriteObject(const char* name, const WCHAR* textureFileName, int xCount, int yCount) = 0;
	virtual void DrawSprite(FXMMATRIX world, ISpriteObject* sprite) = 0;
	virtual void DrawFont(const wchar_t* text, float posX, float posY, float width, float height) = 0;
};

extern "C" RENDERERLIBRARY_API void CreateRenderer(IRenderer** ppRenderer);
extern "C" RENDERERLIBRARY_API void DeleteRenderer(IRenderer* pRenderer);
