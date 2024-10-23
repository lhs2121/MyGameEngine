#include "pch.h"
#include "Material.h"
#include "Renderer.h"

CMaterial::~CMaterial()
{
	if (m_pVertexShader)
		m_pVertexShader->Release();

	if (m_pPixelShader)
		m_pPixelShader->Release();

	if (m_pSamplerState)
		m_pSamplerState->Release();

	if (m_pRasterizerState)
		m_pRasterizerState->Release();

	if (m_pBlendState)
		m_pBlendState->Release();

	if (m_pDepthStencilState)
		m_pDepthStencilState->Release();

	if(m_pCompiledVertexShader)
		m_pCompiledVertexShader->Release();

	if (m_pCompiledPixelShader)
		m_pCompiledPixelShader->Release();


}


void CMaterial::Draw(ID3D11DeviceContext* pDeviceContext)
{
	if (m_pVertexShader)
	pDeviceContext->VSSetShader(m_pVertexShader, nullptr, 0);

	if (m_pPixelShader)
	pDeviceContext->PSSetShader(m_pPixelShader, nullptr, 0);

	if(m_pSamplerState)
		pDeviceContext->PSSetSamplers(0, 1, &m_pSamplerState);

	if (m_pShaderResourceView)
	pDeviceContext->PSSetShaderResources(0, 1, &m_pShaderResourceView);

	if (m_pRasterizerState)
	pDeviceContext->RSSetState(m_pRasterizerState);

	if (m_pBlendState)
	pDeviceContext->OMSetBlendState(m_pBlendState, nullptr, 0xFFFFFFFF);

	if (m_pDepthStencilState)
	pDeviceContext->OMSetDepthStencilState(m_pDepthStencilState, 0);
}

CMaterial* CMaterial::Copy()
{
	CMaterial* pMaterial = new CMaterial;
	pMaterial = this;

	return pMaterial;
}
