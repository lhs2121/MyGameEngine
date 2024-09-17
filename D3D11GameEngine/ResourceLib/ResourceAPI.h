#pragma once
#include <common\declspec.h>
#include <d3d11.h>
#include "ResourceType.h"
struct float4;

namespace Device
{
	extern "C" ResourceAPI void Create(HWND* pHwnd, float4 WindowSize);

	extern "C" ResourceAPI void Delete();

	extern "C" ResourceAPI void InitMesh();

	extern "C" ResourceAPI void InitMaterial();

	extern "C" ResourceAPI void Clear();

	extern "C" ResourceAPI void Present();

	extern "C" ResourceAPI ID3D11Device* GetDevice();

	extern "C" ResourceAPI ID3D11DeviceContext* GetContext();
};

namespace Resource
{
	extern "C" ResourceAPI Texture*        CreateTexture(const char* _path);

	extern "C" ResourceAPI VertexBuffer*   CreateVertexBuffer(const char* _name, void* pVertexStruct, UINT _structSize, UINT _formatSize);

	extern "C" ResourceAPI IndexBuffer*    CreateIndexBuffer(const char* _name, void* pIndexStruct, UINT _structSize);

	extern "C" ResourceAPI InputLayout *   CreateInputLayout(const char* _name, VertexShader* _pShader);
	
	extern "C" ResourceAPI VertexShader*   CreateVertexShader(const char* _name, const char* _path);

	extern "C" ResourceAPI PixelShader*    CreatePixelShader(const char* _name, const char* _path);

	extern "C" ResourceAPI Rasterizer*     CreateRasterizer(const char* _name, D3D11_RASTERIZER_DESC _desc);

	extern "C" ResourceAPI DepthStencil*   CreateDepthStencil(const char* _name, D3D11_DEPTH_STENCIL_DESC _desc);

	extern "C" ResourceAPI Sampler*        CreateSampler(const char* _name, D3D11_SAMPLER_DESC _desc);

	extern "C" ResourceAPI ConstantBuffer* CreateConstantBuffer(const char* _name, void* _pData, int _dataSize, ShaderType _type);

	extern "C" ResourceAPI Blend*          CreateBlend(const char* _name, D3D11_BLEND_DESC _desc);

	extern "C" ResourceAPI Mesh*           CreateMesh(const char* _name);

	extern "C" ResourceAPI Material*       CreateMaterial(const char* _name);

	extern "C" ResourceAPI Texture*        FindTexture(const char* _name);

	extern "C" ResourceAPI VertexBuffer*   FindVertexBuffer(const char* _name);

	extern "C" ResourceAPI IndexBuffer*    FindIndexBuffer(const char* _name);

	extern "C" ResourceAPI InputLayout *   FindInputLayout(const char* _name);

	extern "C" ResourceAPI VertexShader*   FindVertexShader(const char* _name);

	extern "C" ResourceAPI PixelShader*    FindPixelShader(const char* _name);

	extern "C" ResourceAPI Rasterizer*     FindRasterizer(const char* _name);

	extern "C" ResourceAPI DepthStencil*   FindDepthStencil(const char* _name);

	extern "C" ResourceAPI Sampler*        FindSampler(const char* _name);

	extern "C" ResourceAPI ConstantBuffer* FindConstantBuffer(const char* _name);

	extern "C" ResourceAPI Blend*          FindBlend(const char* _name);

	extern "C" ResourceAPI Mesh*           FindMesh(const char* _name);

	extern "C" ResourceAPI Material*       FindMaterial(const char* _name);

	extern "C" ResourceAPI void            DeleteAllResource();
}

