#include "pch.h"
#include "Mesh.h"

CMesh::~CMesh()
{
	if (m_pVertexBuffer)
		m_pVertexBuffer->Release();

	if (m_pIndexBuffer)
		m_pIndexBuffer->Release();
}

void CMesh::Draw(ID3D11DeviceContext* pDeviceContext)
{
	if(m_pVertexBuffer)
		pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &m_vertexStrides, &m_vbOffset);

 	if(m_pIndexBuffer)
		pDeviceContext->IASetIndexBuffer(m_pIndexBuffer,DXGI_FORMAT_R16_UINT, 0);
}
