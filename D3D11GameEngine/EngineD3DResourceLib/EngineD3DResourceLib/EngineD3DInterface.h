#pragma once

struct IEngineUnknown
{
	virtual void Release() = 0;
	virtual ~IEngineUnknown() {}
};

struct IEnginePipeLineRes : public IEngineUnknown
{
	virtual void IntoPipeLine() = 0;
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


struct IEngineTexture : public IEngineUnknown
{
	virtual void Setting(const char* _FilePath) = 0;
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

struct IEngineD3DManager : public IEngineUnknown
{
	virtual IEngineDevice*       CreateDevice() = 0;
	virtual IEngineVertexBuffer* CreateVertexBuffer  (EngineString _Name) = 0;
	virtual IEngineIndexBuffer*  CreateIndexBuffer   (EngineString _Name) = 0;
	virtual IEngineInputLayout*  CreateInputLayout   (EngineString _Name) = 0;
	virtual IEngineVertexShader* CreateVertexShader  (EngineString _Name) = 0;
	virtual IEnginePixelShader*  CreatePixelShader   (EngineString _Name) = 0;
	virtual IEngineRasterizer*   CreateRasterizer    (EngineString _Name) = 0;
	virtual IEngineDepthStencil* CreateDepthStencil  (EngineString _Name) = 0;
	virtual IEngineTexture*      CreateTexture       (EngineString _Name) = 0;

	virtual IEngineVertexBuffer* FindVertexBuffer    (const char* _Name) = 0;
	virtual IEngineIndexBuffer*  FindIndexBuffer     (const char* _Name) = 0;
	virtual IEngineInputLayout*  FindInputLayout     (const char* _Name) = 0;
	virtual IEngineVertexShader* FindVertexShader    (const char* _Name) = 0;
	virtual IEngineRasterizer*   FindRasterizer      (const char* _Name) = 0;
	virtual IEnginePixelShader*  FindPixelShader     (const char* _Name) = 0;
	virtual IEngineDepthStencil* FindDepthStencil    (const char* _Name) = 0;
	virtual IEngineTexture*      FindTexture         (const char* _Name) = 0;
};

extern "C" EngineAPI void CreateEngineD3DManager(IEngineD3DManager * *ppManager);