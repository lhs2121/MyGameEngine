#pragma once
#include "EngineVertexFormat.h"
#include "d3d11.h"

struct IEngineDevice
{
	virtual void Clear() = 0;
	virtual void Present() = 0;
	virtual ID3D11Device* GetDevice() = 0;
	virtual ID3D11DeviceContext* GetContext() = 0;
};

struct IEngineD3DUnknown
{
	virtual void IntoPipeLine() = 0;
};

struct IEngineVertexBuffer : public IEngineD3DUnknown
{
};

struct IEngineIndexBuffer : public IEngineD3DUnknown
{
};

struct IEngineInputLayout : public IEngineD3DUnknown
{
};

struct IEngineVertexShader : public IEngineD3DUnknown
{
};

struct IEnginePixelShader : public IEngineD3DUnknown
{
};

struct IEngineRasterizer : public IEngineD3DUnknown
{
};

struct IEngineDepthStencil : public IEngineD3DUnknown
{
};

struct IEngineD3DResourceManger
{
	virtual IEngineDevice* CreateDevice() = 0;
	virtual IEngineVertexBuffer* CreateVertexBuffer(const char* _Name) = 0;
	virtual IEngineIndexBuffer* CreateIndexBuffer(const char* _Name) = 0;
	virtual IEngineInputLayout* CreateInputLayout(const char* _Name) = 0;
	virtual IEngineVertexShader* CreateVertexShader(const char* _Name) = 0;
	virtual IEnginePixelShader* CreatePixelShader(const char* _Name) = 0;
	virtual IEngineRasterizer* CreateRasterizer(const char* _Name) = 0;
	virtual IEngineDepthStencil* CreateDepthStencil(const char* _Name) = 0;

	virtual void SettingDevice() = 0;
	virtual void SettingVertexBuffer(IEngineVertexBuffer* pBuffer, VERTEX_POS_COLOR* pVertices, int VertexSize) = 0;
	virtual void SettingIndexBuffer(IEngineIndexBuffer* pBuffer, UINT* Indices, int VertexSize) = 0;
	virtual void SettingInputLayout(IEngineInputLayout* pLayout, UINT _ElementNum, D3D11_INPUT_ELEMENT_DESC* _Desc, void* ShaderBytecode, SIZE_T BytecodeLength) = 0;
	virtual void SettingVertexShader(IEngineVertexShader* pShader, const char* _Name, const char* _Path) = 0;
	virtual void SettingPixelShader(IEnginePixelShader* pShader, const char* _Name, const char* _Path) = 0;
	virtual void SettingRasterizer(IEngineRasterizer* pRasterizer, D3D11_RASTERIZER_DESC _Desc) = 0;
	virtual void SettingDepthStencil(IEngineDepthStencil* pDepthStencil, D3D11_DEPTH_STENCIL_DESC _Desc) = 0;

	virtual void* Find(const char* _Name) = 0;
};