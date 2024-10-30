#include "pch.h"
#include "Material.h"
#include "Renderer.h"

void CMaterial::Draw(ID3D11DeviceContext* pDeviceContext)
{
	if (m_pVertexShader)
		pDeviceContext->VSSetShader(m_pVertexShader, nullptr, 0);

	if (m_pPixelShader)
		pDeviceContext->PSSetShader(m_pPixelShader, nullptr, 0);

	if (m_pShaderResourceView)
		pDeviceContext->PSSetShaderResources(0, 1, &m_pShaderResourceView);

	if (m_pSamplerState)
		pDeviceContext->PSSetSamplers(0, 1, &m_pSamplerState);

	if (m_pRasterizerState)
		pDeviceContext->RSSetState(m_pRasterizerState);

	if (m_pBlendState)
		pDeviceContext->OMSetBlendState(m_pBlendState, nullptr, 0xFFFFFFFF);

	if (m_pDepthStencilState)
		pDeviceContext->OMSetDepthStencilState(m_pDepthStencilState, 0);
}

void CMaterial::SetShader(const WCHAR* wszFileName)
{
	ShaderData* data = m_pRenderer->GetShader(wszFileName);
	m_pVertexShader = data->m_pVertexShader;
	m_pPixelShader = data->m_pPixelShader;
	m_pCompiledVertexShader = data->m_pCompiledVertexShader;
}

void CMaterial::SetTexture(const WCHAR* wszFileName)
{
	m_pShaderResourceView = m_pRenderer->GetShaderResourceView(wszFileName);
}

void CMaterial::SetRasterizer(const char* name)
{
	m_pRasterizerState = m_pRenderer->GetRasterizer(name);
}

void CMaterial::SetDepthStencil(const char* name)
{
	m_pDepthStencilState = m_pRenderer->GetDepthStencil(name);
}

void CMaterial::SetSampler(const char* name)
{
	m_pSamplerState = m_pRenderer->GetSampler(name);
}

void CMaterial::SetBlend(const char* name)
{
	m_pBlendState = m_pRenderer->GetBlend(name);
}


