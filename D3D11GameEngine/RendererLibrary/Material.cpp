#include "pch.h"
#include "Material.h"
#include "Renderer.h"

CMaterial* CMaterial::Copy()
{
	CMaterial* pMaterial = new CMaterial;
	pMaterial = this;

	return pMaterial;
}

void CMaterial::Draw(ID3D11DeviceContext* pDeviceContext)
{
	if (m_pVertexShader)
	pDeviceContext->VSSetShader(m_pVertexShader, nullptr, 0);

	if (m_pPixelShader)
	pDeviceContext->PSSetShader(m_pPixelShader, nullptr, 0);

	if (m_pShaderResourceView)
	pDeviceContext->PSSetShaderResources(0, 1, &m_pShaderResourceView);
}

void CMaterial::SetTexture(const WCHAR* wszTexName)
{
	m_pShaderResourceView = m_pRenderer->GetShaderResourceView(wszTexName);
}

