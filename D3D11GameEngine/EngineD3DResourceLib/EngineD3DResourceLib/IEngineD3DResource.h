#pragma once

struct IEngineD3DResource
{
	virtual void Release() = 0;
	virtual ~IEngineD3DResource() {}
};

struct IEnginePipeLineResource : public IEngineD3DResource
{
	virtual void IntoPipeLine() = 0;
};

struct IEngineDevice : public IEngineD3DResource
{
	virtual void Init(void* pHwnd, float4 WindowSize) = 0;
	virtual void ResourceInit(void* pManager) = 0;
	virtual void Clear() = 0;
	virtual void Present() = 0;
	virtual ID3D11Device* GetDevice() = 0;
	virtual ID3D11DeviceContext* GetContext() = 0;
};


struct IEngineTexture : public IEngineD3DResource
{
	virtual void Setting(const char* _FilePath) = 0;
};

struct IEngineVertexBuffer : public IEnginePipeLineResource
{
	virtual void Setting(void* pVertices, int VertexFormatSize, int VertexSize) = 0;
};

struct IEngineIndexBuffer : public IEnginePipeLineResource
{
	virtual void Setting(UINT* Indices, int IndexSize) = 0;
	virtual UINT GetIndexCount() = 0;
};

struct IEngineInputLayout : public IEnginePipeLineResource
{
	virtual void Setting(D3D11_INPUT_ELEMENT_DESC* _Desc, UINT _ElementNum, void* ShaderBytecode, SIZE_T BytecodeLength) = 0;
};

struct IEngineVertexShader : public IEnginePipeLineResource
{
	virtual void Setting(const char* _Name, const char* _Path) = 0;
};

struct IEnginePixelShader : public IEnginePipeLineResource
{
	virtual void Setting(const char* _Name, const char* _Path) = 0;
};

struct IEngineRasterizer : public IEnginePipeLineResource
{
	virtual void Setting(D3D11_RASTERIZER_DESC _Desc) = 0;
};

struct IEngineDepthStencil : public IEnginePipeLineResource
{
	virtual void Setting(D3D11_DEPTH_STENCIL_DESC _Desc) = 0;
};

struct IEngineD3DResourceManager : public IEngineD3DResource
{ 
	virtual IEngineDevice* CreateDevice() = 0;
	virtual IEngineVertexBuffer* CreateVertexBuffer(const char* _Name) = 0;
	virtual IEngineIndexBuffer* CreateIndexBuffer(const char* _Name) = 0;
	virtual IEngineInputLayout* CreateInputLayout(const char* _Name) = 0;
	virtual IEngineVertexShader* CreateVertexShader(const char* _Name) = 0;
	virtual IEnginePixelShader* CreatePixelShader(const char* _Name) = 0;
	virtual IEngineRasterizer* CreateRasterizer(const char* _Name) = 0;
	virtual IEngineDepthStencil* CreateDepthStencil(const char* _Name) = 0;
	virtual IEngineTexture* CreateTexture(const char* _Name) = 0;

	virtual IEngineVertexBuffer* FindVertexBuffer(const char* _Name) = 0;
	virtual IEngineIndexBuffer* FindIndexBuffer(const char* _Name) = 0;
	virtual IEngineInputLayout* FindInputLayout(const char* _Name) = 0;
	virtual IEngineVertexShader* FindVertexShader(const char* _Name) = 0;
	virtual IEngineRasterizer* FindRasterizer(const char* _Name) = 0;
	virtual IEnginePixelShader* FindPixelShader(const char* _Name) = 0;
	virtual IEngineDepthStencil* FindDepthStencil(const char* _Name) = 0;
	virtual IEngineTexture* FindTexture(const char* _Name) = 0;
};

extern "C" __declspec(dllexport) void CreateD3DResourceManger(IEngineD3DResourceManager * *ppManager);