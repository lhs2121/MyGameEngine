#pragma once
#include "IRenderer.h"

class CRenderer;
class CMaterial : public IMaterial
{
public:
	~CMaterial();
	CMaterial* Copy();
	void Draw(ID3D11DeviceContext* pDeviceContext);

	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;

	ID3D11DepthStencilState* m_pDepthStencilState = nullptr;
	ID3D11RasterizerState* m_pRasterizerState = nullptr;
	ID3D11SamplerState* m_pSamplerState = nullptr;
	ID3D11BlendState* m_pBlendState = nullptr;
	ID3D11ShaderResourceView* m_pShaderResourceView = nullptr;

	ID3DBlob* m_pCompiledVertexShader = nullptr;
	ID3DBlob* m_pCompiledPixelShader = nullptr;

	std::vector<IUnknown*> m_deleteResources;
};