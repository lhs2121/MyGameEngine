#pragma once
#include "IEngineD3DRes.h"

class EngineD3DResourceManger : public IEngineD3DResourceManger
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

	void SettingDevice() override;
	void SettingVertexBuffer(IEngineVertexBuffer* pBuffer, VERTEX_POS_COLOR* pVertices, int VertexSize) override;
	void SettingIndexBuffer(IEngineIndexBuffer* pBuffer, UINT* Indices, int VertexSize) override;
	void SettingInputLayout(IEngineInputLayout* pLayout, UINT _ElementNum, D3D11_INPUT_ELEMENT_DESC* _Desc, void* ShaderBytecode, SIZE_T BytecodeLength) override;
	void SettingVertexShader(IEngineVertexShader* pShader, const char* _Name, const char* _Path) override;
	void SettingPixelShader(IEnginePixelShader* pShader, const char* _Name, const char* _Path) override;
	void SettingRasterizer(IEngineRasterizer* pRasterizer, D3D11_RASTERIZER_DESC _Desc) override;
	void SettingDepthStencil(IEngineDepthStencil* pDepthStencil, D3D11_DEPTH_STENCIL_DESC _Desc) override;

	void* Find(const char* _Name) override;
private:
	IEngineDevice* m_pDevice = nullptr;
	std::map<const char*, IEngineD3DUnknown*> ResourceMap;
};