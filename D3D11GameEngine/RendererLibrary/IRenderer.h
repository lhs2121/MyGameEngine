#pragma once
#include <DirectXMath.h>
#include "d3d11.h"
#include "Windows.h"

#ifdef RendererLibrary
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI __declspec(dllimport)
#endif 

using namespace DirectX;

struct IMesh
{
};

struct IMaterial
{
	virtual void SetTexture(const WCHAR* wszTexName) = 0;
};
struct ISpriteObject
{
	virtual IMaterial* GetMaterial() = 0;
	virtual void CreateAnimation(const WCHAR* wszTexName, int countX, int countY, float interTime) = 0;
	virtual void UpdateAnimation(float deltaTime) = 0;
};
struct IRenderer
{
	virtual void Initalize(UINT winSizeX, UINT winSizeY, HWND& hwnd) = 0;

	virtual void StartRender() = 0;
	virtual void EndRender() = 0;

	virtual void LoadTexture(const WCHAR* wszFilePath) = 0;
	virtual void LoadShader(const WCHAR* wszShaderPath) = 0;

	virtual ISpriteObject* CreateSpriteObject(const char* name) = 0;

	virtual void DrawRect(const XMMATRIX& matWorld, const XMVECTOR& color) = 0;
	virtual void DrawSprite(const XMMATRIX& matWorld, ISpriteObject* pSpriteObject) = 0;
};

extern "C" DLLAPI void CreateRenderer(IRenderer** ppRenderer);
extern "C" DLLAPI void DeleteRenderer(IRenderer* pRenderer);