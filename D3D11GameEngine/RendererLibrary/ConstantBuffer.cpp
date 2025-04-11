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

void Transform::TransformUpdate()
{
	XMVECTOR scale = m_vecScale * child->m_vecScale;
	XMVECTOR rot = m_vecRotation + child->m_vecRotation;
	XMVECTOR pos = m_vecPosition + child->m_vecPosition;
	XMVECTOR quat = XMQuaternionRotationRollPitchYawFromVector(rot);

	XMMATRIX scalemat = XMMatrixScalingFromVector(scale);
	XMMATRIX rotmat = XMMatrixRotationRollPitchYawFromVector(rot);
	XMMATRIX posmat = XMMatrixTranslationFromVector(pos);

	m_matWorld = scalemat * rotmat * posmat;
}

void Transform::SetScale(CXMVECTOR scale)
{
	m_vecScale = scale;
}

void Transform::SetRotation(CXMVECTOR rot)
{
	m_vecRotation = rot;
}

void Transform::SetPos(CXMVECTOR pos)
{
	m_vecPosition = pos;
}

void Transform::AddScale(CXMVECTOR scale)
{
	m_vecScale += scale;
}

void Transform::AddRotation(CXMVECTOR rot)
{
	m_vecRotation += rot;
}

void Transform::AddPos(CXMVECTOR pos)
{
	m_vecPosition += pos;
}
