#pragma once
#include "d3d11.h"
#include "Windows.h"

#ifdef RENDERERLIBRARY_EXPORTS
#define RENDERERLIBRARY_API __declspec(dllexport)
#else
#define RENDERERLIBRARY_API __declspec(dllimport)
#endif 

struct BlockTile
{
	unsigned short tileIndex = 0;
	unsigned char visible = 1;
	unsigned char reserved = 0;
};

struct BlockGridDesc
{
	const WCHAR* textureFile = nullptr;
	const BlockTile* tiles = nullptr;
	int width = 0;
	int height = 0;
	int atlasColumns = 1;
	int atlasRows = 1;
	float tileSize = 16.0f;
	float originX = 0.0f;
	float originY = 0.0f;
};

struct IRenderer
{
	virtual void Initialize(UINT winSizeX, UINT winSizeY, HWND& hwnd) = 0;

	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;

	virtual void LoadTexture(const WCHAR* textureFile) = 0;
	virtual void DrawBlockGrid(const BlockGridDesc& desc) = 0;
};

extern "C" RENDERERLIBRARY_API void CreateRenderer(IRenderer** ppRenderer);
extern "C" RENDERERLIBRARY_API void DeleteRenderer(IRenderer* pRenderer);
