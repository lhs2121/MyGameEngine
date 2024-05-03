#pragma once
#include "d3d11.h"

struct VERTEX_POS
{
	float4 Pos;
};

struct VERTEX_POS_COLOR
{
	float4 Pos;
	float4 Color;
};
struct VERTEX_POSTEXCOORD
{
	float4 Pos;
	float4 TexCoord;
};

struct IEngineDevice
{
	virtual void Init(void* pHwnd,float4 WindowSize) = 0;
	virtual void ResourceInit() = 0;
	virtual void Clear() = 0;
	virtual void Present() = 0;
	virtual ID3D11Device* GetDevice() = 0;
	virtual ID3D11DeviceContext* GetContext() = 0;
	virtual ~IEngineDevice()
	{
	};
};

struct IEngineD3DUnknown
{
	virtual void IntoPipeLine() = 0;
};

struct IEngineVertexBuffer : public IEngineD3DUnknown
{
	virtual ~IEngineVertexBuffer()
	{
	};
};

struct IEngineIndexBuffer : public IEngineD3DUnknown
{
	virtual ~IEngineIndexBuffer()
	{
	};
};

struct IEngineInputLayout : public IEngineD3DUnknown
{
	virtual ~IEngineInputLayout()
	{
	};
};

struct IEngineVertexShader : public IEngineD3DUnknown
{
	virtual ~IEngineVertexShader() 
	{
	};
};

struct IEnginePixelShader : public IEngineD3DUnknown
{
	virtual ~IEnginePixelShader() 
	{
	};
};

struct IEngineRasterizer : public IEngineD3DUnknown
{
	virtual ~IEngineRasterizer() 
	{
	};
};

struct IEngineDepthStencil : public IEngineD3DUnknown
{
	virtual ~IEngineDepthStencil() 
	{
	};
};

struct IEngineD3DResourceManager
{
	virtual IEngineDevice* CreateDevice() = 0;
	virtual IEngineVertexBuffer* CreateVertexBuffer(const char* _Name) = 0;
	virtual IEngineIndexBuffer* CreateIndexBuffer(const char* _Name) = 0;
	virtual IEngineInputLayout* CreateInputLayout(const char* _Name) = 0;
	virtual IEngineVertexShader* CreateVertexShader(const char* _Name) = 0;
	virtual IEnginePixelShader* CreatePixelShader(const char* _Name) = 0;
	virtual IEngineRasterizer* CreateRasterizer(const char* _Name) = 0;
	virtual IEngineDepthStencil* CreateDepthStencil(const char* _Name) = 0;

	virtual void SettingVertexBuffer(IEngineVertexBuffer* pBuffer, VERTEX_POS_COLOR* pVertices, int VertexSize) = 0;
	virtual void SettingIndexBuffer(IEngineIndexBuffer* pBuffer, UINT* Indices, int VertexSize) = 0;
	virtual void SettingInputLayout(IEngineInputLayout* pLayout, UINT _ElementNum, D3D11_INPUT_ELEMENT_DESC* _Desc, void* ShaderBytecode, SIZE_T BytecodeLength) = 0;
	virtual void SettingVertexShader(IEngineVertexShader* pShader, const char* _Name, const char* _Path) = 0;
	virtual void SettingPixelShader(IEnginePixelShader* pShader, const char* _Name, const char* _Path) = 0;
	virtual void SettingRasterizer(IEngineRasterizer* pRasterizer, D3D11_RASTERIZER_DESC _Desc) = 0;
	virtual void SettingDepthStencil(IEngineDepthStencil* pDepthStencil, D3D11_DEPTH_STENCIL_DESC _Desc) = 0;

	virtual IEngineVertexBuffer* FindVertexBuffer(const char* _Name) = 0;
	virtual IEngineIndexBuffer* FindIndexBuffer(const char* _Name) = 0;
	virtual IEngineInputLayout* FindInputLayout(const char* _Name) = 0;
	virtual IEngineVertexShader* FindVertexShader(const char* _Name) = 0;
	virtual IEngineRasterizer* FindRasterizer(const char* _Name) = 0;
	virtual IEnginePixelShader* FindPixelShader(const char* _Name) = 0;
	virtual IEngineDepthStencil* FindDepthStencil(const char* _Name) = 0;

	virtual void DeleteAllResource() = 0;

	virtual ~IEngineD3DResourceManager()
	{
	};
};

extern "C" __declspec(dllexport) void CreateD3DResourceManger(IEngineD3DResourceManager** ppManager);