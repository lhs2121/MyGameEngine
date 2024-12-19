#pragma once
#include "d3d11.h"
#include <BaseLibrary/Interface.h>

struct SimpleVertex
{
	float4 POSITION;
	float2 TEXCOORD;
};

struct ShaderData
{
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3DBlob* m_pCompiledVertexShader;
};

struct SpriteData
{
	float2 ratio = { 1.0f, 1.0f };
	float2 offset = { 0.0f, 0.0f };
};