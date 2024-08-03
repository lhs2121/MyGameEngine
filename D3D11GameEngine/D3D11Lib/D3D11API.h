#pragma once
#include <common\declspec.h>
#include <d3d11.h>
struct IEngineD3DManager;

enum class ResType
{
	Mesh,
	Material,
	VB,
	IB,
	CB,
	IA,
	VS,
	PS,
	RS,
	DS,
	Sampler,
	Texture,
};

enum class ShaderType
{
	VS,
	PS,
	CS,
	HS,
	DS,
	GS
};

enum class ShaderInput
{
	POSITION,
	TEXCOORD,
	COLOR,
	NORMAL,
};

struct IEngineDevice
{
	virtual void Init(void* pHwnd, float4 WindowSize) = 0;
	virtual void ResourceInit(IEngineD3DManager* pManager) = 0;
	virtual void Clear() = 0;
	virtual void Present() = 0;
	virtual ID3D11Device* GetDevice() = 0;
	virtual ID3D11DeviceContext* GetContext() = 0;
};

struct IEngineUnknown
{
	virtual ~IEngineUnknown() {};
	virtual void SetDevice(ID3D11Device* _DevicePtr) = 0;
	virtual void SetContext(ID3D11DeviceContext* _ContextPtr) = 0;
};

struct IEnginePipeLineRes : public IEngineUnknown
{
	virtual void IntoPipeline() = 0;
};

struct IEngineShaderResource : public IEngineUnknown
{
	virtual void IntoPipeline(ShaderType _Type, int SlotNum = 0) = 0;
};

struct IEngineVertexBuffer : public IEnginePipeLineRes
{
	virtual void Setting(void* pVertices, int VertexFormatSize, int VertexSize, UINT _SlotNumber) = 0;
};

struct IEngineIndexBuffer : public IEnginePipeLineRes
{
	virtual void Setting(UINT* Indices, int IndexSize) = 0;
};

struct IEngineVertexShader : public IEnginePipeLineRes
{
	virtual void Setting(EngineString _Name, EngineString _Path) = 0;
};

struct IEngineInputLayout : public IEnginePipeLineRes
{
	virtual void SetDesc(ShaderInput* _ShaderInputArray, UINT _ArrayCount) = 0;
	virtual void Setting(IEngineVertexBuffer* _pVB, IEngineVertexShader* _pVS) = 0;
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

struct IMesh : public IEnginePipeLineRes
{
	virtual void Setting(const char* _VBName, const char* _IBName) = 0;
	virtual void IntoPipeline() = 0;

	virtual IEngineVertexBuffer* GetVB() = 0;
	virtual UINT GetIndexCount() = 0;
};

struct IMaterial : public IEnginePipeLineRes
{
	virtual void Setting(const char* _ShaderName) = 0;
	virtual void IntoPipeline() = 0;

	virtual IEngineVertexShader* GetVS() = 0;
	virtual void SetSampler(const char* _SamplerName) = 0;
	virtual void SetTexture(const char* _TextureName) = 0;
};

struct IEngineD3DManager
{
	virtual IEngineDevice* CreateDevice() = 0;
	virtual void* CreateResource(ResType _Type, EngineString _Name) = 0;
	virtual void* Find(ResType _Type, const char* _Name) = 0;
	virtual IEngineInputLayout* FindIA(IMesh* _Mesh, IMaterial* _Material) = 0;
};

extern "C" D3D11API void CreateEngineD3DManager(IEngineD3DManager * *ppEngineManager);
extern "C" D3D11API void DeleteEngineD3DManager(IEngineD3DManager * pEngineManager);