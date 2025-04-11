#include "pch.h"
#include "MeshObject.h"

void MeshObject::Draw(ID3D11DeviceContext* pContext)
{
	if (m_pVertexBuffer)
		pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &m_stride, &m_offset);

	if (m_pIndexBuffer)
		pContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	if (m_pVertexShader)
		pContext->VSSetShader(m_pVertexShader, nullptr, 0);

	if (m_pPixelShader)
		pContext->PSSetShader(m_pPixelShader, nullptr, 0);

	if (m_pShaderResourceView)
		pContext->PSSetShaderResources(0, 1, &m_pShaderResourceView);

	if (m_pSampler)
		pContext->PSSetSamplers(0, 1, &m_pSampler);

	if (m_pRasterizer)
		pContext->RSSetState(m_pRasterizer);

	if (m_pBlend)
		pContext->OMSetBlendState(m_pBlend, nullptr, 0xFFFFFFFF);

	if (m_pDepthStencil)
		pContext->OMSetDepthStencilState(m_pDepthStencil, 0);

	m_pTransformBuffer->Bind(pContext);

	pContext->DrawIndexed(m_indexCount, 0, 0);
}

void MeshObject::SetSolid()
{
}

void MeshObject::SetWireFrame()
{
}
