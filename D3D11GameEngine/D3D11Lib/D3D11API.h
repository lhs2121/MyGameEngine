#pragma once
#include <common\declspec.h>
#include <d3d11.h>
enum class ShaderType
{
	VS,
	PS,
	CS,
	HS,
	DS,
	GS
};

struct IEngineUnknown
{
	virtual void Release() = 0;
	virtual ~IEngineUnknown() {}
};

struct IEnginePipeLineRes : public IEngineUnknown
{
	virtual void IntoPipeLine() = 0;
};

struct IEngineShaderResource : public IEngineUnknown
{
	virtual void IntoPipeLine(ShaderType _Type,int SlotNum = 0) = 0;
};

struct IEngineDevice : public IEngineUnknown
{
	virtual void Init(void* pHwnd, float4 WindowSize) = 0;
	virtual void ResourceInit(void* pManager) = 0;
	virtual void Clear() = 0;
	virtual void Present() = 0;
	virtual ID3D11Device* GetDevice() = 0;
	virtual ID3D11DeviceContext* GetContext() = 0;
};

struct IEngineVertexBuffer : public IEnginePipeLineRes
{
	virtual void Setting(void* pVertices, int VertexFormatSize, int VertexSize) = 0;
};

struct IEngineIndexBuffer : public IEnginePipeLineRes
{
	virtual void Setting(UINT* Indices, int IndexSize) = 0;
	virtual UINT GetIndexCount() = 0;
};

struct IEngineInputLayout : public IEnginePipeLineRes
{
	virtual void Setting(D3D11_INPUT_ELEMENT_DESC* _Desc, UINT _ElementNum, void* ShaderBytecode, SIZE_T BytecodeLength) = 0;
};

struct IEngineVertexShader : public IEnginePipeLineRes
{
	virtual void Setting(EngineString _Name, EngineString _Path) = 0;
};

struct IEnginePixelShader : public IEnginePipeLineRes
{
	virtual void Setting(EngineString _Name, EngineString _Path) = 0;
};

struct IEngineRasterizer : public IEnginePipeLineRes
{
	virtual void Setting(D3D11_RASTERIZER_DESC _Desc) = 0;
};

struct IEngineDepthStencil : public IEnginePipeLineRes
{
	virtual void Setting(D3D11_DEPTH_STENCIL_DESC _Desc) = 0;
};

struct IEngineTexture : public IEngineShaderResource
{
	virtual ID3D11ShaderResourceView* GetSRV() = 0;
	virtual float4 GetImageScale() = 0;
	virtual void Setting(EngineFile& _File) = 0;
};

struct IEngineSampler : public IEngineShaderResource
{
	virtual ID3D11SamplerState* GetState() = 0;
	virtual void Setting(D3D11_SAMPLER_DESC* DescPtr) = 0;
};

struct IEngineConstantBuffer : public IEngineShaderResource
{
	virtual void Setting(D3D11_BUFFER_DESC Desc, void* _DataPtr, int _DataSize) = 0;
};

struct IEngineD3DManager : public IEngineUnknown
{
	virtual IEngineDevice*           CreateDevice          ()                   = 0;
	virtual IEngineVertexBuffer*     CreateVertexBuffer    (EngineString _Name) = 0;
	virtual IEngineIndexBuffer*      CreateIndexBuffer     (EngineString _Name) = 0;
	virtual IEngineInputLayout*      CreateInputLayout     (EngineString _Name) = 0;
	virtual IEngineVertexShader*     CreateVertexShader    (EngineString _Name) = 0;
	virtual IEnginePixelShader*      CreatePixelShader     (EngineString _Name) = 0;
	virtual IEngineRasterizer*       CreateRasterizer      (EngineString _Name) = 0;
	virtual IEngineDepthStencil*     CreateDepthStencil    (EngineString _Name) = 0;
	virtual IEngineTexture*          CreateTexture         (EngineString _Name) = 0;
	virtual IEngineSampler*          CreateSampler         (EngineString _Name) = 0;
	virtual IEngineConstantBuffer*   CreateConstantBuffer  (EngineString _Name) = 0;
								     
	virtual IEngineVertexBuffer*     FindVertexBuffer      (EngineString _Name) = 0;
	virtual IEngineIndexBuffer*      FindIndexBuffer       (EngineString _Name) = 0;
	virtual IEngineInputLayout*      FindInputLayout       (EngineString _Name) = 0;
	virtual IEngineVertexShader*     FindVertexShader      (EngineString _Name) = 0;
	virtual IEngineRasterizer*       FindRasterizer        (EngineString _Name) = 0;
	virtual IEnginePixelShader*      FindPixelShader       (EngineString _Name) = 0;
	virtual IEngineDepthStencil*     FindDepthStencil      (EngineString _Name) = 0;
	virtual IEngineTexture*          FindTexture           (EngineString _Name) = 0;
	virtual IEngineSampler*          FindSampler           (EngineString _Name) = 0;
	virtual IEngineConstantBuffer*   FindConstantBuffer    (EngineString _Name) = 0;
};

extern "C" D3D11API void CreateEngineD3DManager(IEngineD3DManager** ppEngineManager);
extern "C" D3D11API void DeleteEngineD3DManager(IEngineD3DManager* pEngineManager);