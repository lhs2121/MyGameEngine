#pragma once
#include "IEngineD3DRes.h"

class EngineD3DResourceManager : public IEngineD3DResourceManager
{
public:
	IEngineDevice* CreateDevice() override;
	IEngineVertexBuffer* CreateVertexBuffer(const char* _Name) override;
	IEngineIndexBuffer* CreateIndexBuffer(const char* _Name) override;
	IEngineInputLayout* CreateInputLayout(const char* _Name) override;
	IEngineVertexShader* CreateVertexShader(const char* _Name) override;
	IEnginePixelShader* CreatePixelShader(const char* _Name) override;
	IEngineRasterizer* CreateRasterizer(const char* _Name) override;
	IEngineDepthStencil* CreateDepthStencil(const char* _Name) override;

	void SettingVertexBuffer(IEngineVertexBuffer* pBuffer, void* pVertices, int VertexFormatSize, int VertexSize) override;
	void SettingIndexBuffer(IEngineIndexBuffer* pBuffer, UINT* Indices, int VertexSize) override;
	void SettingInputLayout(IEngineInputLayout* pLayout, D3D11_INPUT_ELEMENT_DESC* _Desc,
		UINT _ElementNum, void* ShaderBytecode, SIZE_T BytecodeLength) override;
	void SettingVertexShader(IEngineVertexShader* pShader, const char* _Name, const char* _Path) override;
	void SettingPixelShader(IEnginePixelShader* pShader, const char* _Name, const char* _Path) override;
	void SettingRasterizer(IEngineRasterizer* pRasterizer, D3D11_RASTERIZER_DESC _Desc) override;
	void SettingDepthStencil(IEngineDepthStencil* pDepthStencil, D3D11_DEPTH_STENCIL_DESC _Desc) override;

	IEngineVertexBuffer* FindVertexBuffer(const char* _Name) override;
	IEngineIndexBuffer* FindIndexBuffer(const char* _Name) override;
	IEngineInputLayout* FindInputLayout(const char* _Name) override;
	IEngineVertexShader* FindVertexShader(const char* _Name) override;
	IEngineRasterizer* FindRasterizer(const char* _Name) override;
	IEnginePixelShader* FindPixelShader(const char* _Name) override;
	IEngineDepthStencil* FindDepthStencil(const char* _Name) override;

	void DeleteAllResource() override;
private:
	IEngineDevice* Device = nullptr;
	std::map<std::string, IEngineVertexBuffer*> VBMap;
	std::map<std::string, IEngineIndexBuffer*> IBMap;
	std::map<std::string, IEngineInputLayout*> IAMap;
	std::map<std::string, IEngineVertexShader*> VSMap;
	std::map<std::string, IEnginePixelShader*> PSMap;
	std::map<std::string, IEngineRasterizer*> RSMap;
	std::map<std::string, IEngineDepthStencil*> DSMap;
};