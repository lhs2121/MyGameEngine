#pragma once
#include <common\declspec.h>
#include <d3d11.h>
struct IResManager;

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


struct IDevice
{
	virtual void Init(void* pHwnd, float4 WindowSize) = 0;
	virtual void InitMesh(IResManager* pManager) = 0;
	virtual void InitMaterial(IResManager* pManager) = 0;
	virtual void Clear() = 0;
	virtual void Present() = 0;
	virtual ID3D11Device* GetDevice() = 0;
	virtual ID3D11DeviceContext* GetContext() = 0;
};

struct IResBase
{
	virtual ~IResBase() {};
};

struct IRes : public IResBase
{
	virtual void IntoPipeline() = 0;
};

struct IShaderRes : public IResBase
{
	virtual void IntoPipeline(ShaderType _Type, int SlotNum = 0) = 0;
};

struct IVertexBuffer : public IRes
{
	virtual void Setting(void* pVertices, int _Stride, int _ByteWidth, UINT _SlotNumber) = 0;
};

struct IIndexBuffer : public IRes
{
	virtual void Setting(UINT* Indices, int IndexSize) = 0;
};

struct IVertexShader : public IRes
{
	virtual void Setting(EngineString _Name, EngineString _Path) = 0;
};

struct IInputLayout : public IRes
{
	virtual void Setting(IVertexBuffer* _pVB, IVertexShader* _pVS) = 0;
};

struct IPixelShader : public IRes
{
	virtual void Setting(EngineString _Name, EngineString _Path) = 0;
};

struct IRasterizer : public IRes
{
	virtual void Setting(D3D11_RASTERIZER_DESC _Desc) = 0;
};

struct IDepthStencil : public IRes
{
	virtual void Setting(D3D11_DEPTH_STENCIL_DESC _Desc) = 0;
};

struct ITexture : public IShaderRes
{
	virtual ID3D11ShaderResourceView* GetSRV() = 0;
	virtual float4 GetImageScale() = 0;
	virtual void Setting(EngineFile& _File) = 0;
};

struct ISampler : public IShaderRes
{
	virtual ID3D11SamplerState* GetState() = 0;
	virtual void Setting(D3D11_SAMPLER_DESC* DescPtr) = 0;
};

struct IConstantBuffer : public IShaderRes
{
	virtual void Setting(void* _DataPtr, int _sizeofData) = 0;
};

struct IMesh : public IResBase
{
	virtual void Setting(const char* _VBName, const char* _IBName) = 0;
	virtual IVertexBuffer* GetVB() = 0;
	virtual UINT GetIndexCount() = 0;

	virtual void IntoPipeline() = 0;
};

struct IMaterial : public IResBase
{
	virtual void SetShader(const char* _ShaderName) = 0;
	virtual void SetRS(const char* _RSName) = 0;
	virtual void SetDS(const char* _DSName) = 0;
	virtual void SetSampler(const char* _SamplerName) = 0;
	virtual void SetTexture(const char* _TextureName) = 0;
	virtual IVertexShader* GetVS() = 0;

	virtual void IntoPipeline() = 0;
};

struct IResManager
{
	virtual void  CreateDevice(IDevice** ppIDevice) = 0;
	virtual void* CreateResource(ResType _Type, EngineString _Name) = 0;
	virtual void* Find(ResType _Type, const char* _Name) = 0;
	virtual IInputLayout* GenerateInputLayout(IMesh* _Mesh, IMaterial* _Material) = 0;
};

extern "C" D3D11API void CreateResManager(IResManager** ppIResManager);
extern "C" D3D11API void DeleteResManager(IResManager* pIResManager);