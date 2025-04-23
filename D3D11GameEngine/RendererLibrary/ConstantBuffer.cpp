#include "pch.h"
#include "ConstantBuffer.h"

ConstantBuffer::~ConstantBuffer()
{
	if (m_pBuffer)
		m_pBuffer->Release();
}

void ConstantBuffer::Bind(ID3D11DeviceContext* pDeviceContext)
{
	D3D11_MAPPED_SUBRESOURCE m_subResourece;

	if (S_OK != pDeviceContext->Map(m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_subResourece))
		__debugbreak();

	memcpy_s(m_subResourece.pData, m_dataSize, m_pData, m_dataSize);
	pDeviceContext->Unmap(m_pBuffer, 0);

	if (!strcmp(m_szShaderType, "vs"))
	{
		pDeviceContext->VSSetConstantBuffers(m_slot, 1, &m_pBuffer);
		return;
	}
	pDeviceContext->PSSetConstantBuffers(m_slot, 1, &m_pBuffer);
}