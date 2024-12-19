#pragma once
#include "Interface.h"

class CRenderer;
class CMaterial : public IMaterial
{
public:
	void Draw(ID3D11DeviceContext* pDeviceContext);
	void SetShader(const WCHAR* wszFileName) override;
	void SetTexture(const WCHAR* wszFileName) override;
	void SetRasterizer(const char* name) override;
	void SetDepthStencil(const char* name) override;
	void SetSampler(const char* name) override;
	void SetBlend(const char* name) override;


	CRenderer* m_pRenderer = nullptr;
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3DBlob* m_pCompiledVertexShader = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;

	ID3D11RasterizerState* m_pRasterizerState;
	ID3D11SamplerState* m_pSamplerState;
	ID3D11DepthStencilState* m_pDepthStencilState;
	ID3D11BlendState* m_pBlendState;

	ID3D11ShaderResourceView* m_pShaderResourceView = nullptr;
};