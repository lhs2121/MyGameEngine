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

struct IMesh
{
};

struct IMaterial
{
	virtual void SetTexture(const WCHAR* wszFileName) = 0;
	virtual void SetShader(const WCHAR* wszFileName) = 0;
	virtual void SetRasterizer(const char* name) = 0;
	virtual void SetDepthStencil(const char* name) = 0;
	virtual	void SetSampler(const char* name) = 0;
	virtual void SetBlend(const char* name) = 0;
};

struct ISpriteObject
{
	virtual void UpdateAnimation(float deltaTime) = 0;
};
struct IRenderer
{
	virtual void Initialize(UINT winSizeX, UINT winSizeY, HWND& hwnd) = 0;

	virtual void StartRender() = 0;
	virtual void EndRender() = 0;
	virtual void LoadTexture(const WCHAR* wszFilePath) = 0;
	virtual void LoadShader(const WCHAR* wszShaderPath) = 0;

	virtual IMaterial* CreateMaterial(const char* name) = 0;
	virtual ISpriteObject* CreateSpriteObject(const char* name, const WCHAR* wszTexfile, int countX, int countY, float interTime = 0.3f) = 0;

	virtual void DrawRect(const XMMATRIX& matWorld, const XMVECTOR& color) = 0;
	virtual void DrawRect2(float x, float y, float width, float height, const XMVECTOR& color) = 0;
	virtual void DrawSprite(const XMMATRIX& matWorld, ISpriteObject* pSpriteObject) = 0;
	virtual void DrawFont(const wchar_t* str, float x, float y, float width, float height) = 0;
};

extern "C" RENDERERLIBRARY_API void CreateRenderer(IRenderer** ppRenderer);
extern "C" RENDERERLIBRARY_API void DeleteRenderer(IRenderer* pRenderer);