#include "pch.h"
#include "Transform.h"

void Transform::TransformUpdate()
{
	if (!m_IsUpdate)
	{
		return;
	}

	XMMATRIX matLocalScale = XMMatrixScalingFromVector(m_vecScale);
	XMMATRIX matLocalRot = XMMatrixRotationRollPitchYawFromVector(m_vecRot);
	XMMATRIX matLocalPos = XMMatrixTranslationFromVector(m_vecPos);
	
	m_matWorld = matLocalScale * matLocalRot * matLocalPos;
	if (m_pParent)
	{
		if (false == m_pParent->m_IsUpdate)
		{
			m_pParent->TransformUpdate();
		}
		m_matWorld *= m_pParent->m_matWorld;
	}

	m_IsUpdate = true;
}


void Transform::SetScale(CXMVECTOR vecScale)
{
	m_vecScale = vecScale;
	m_vecScale.m128_f32[3] = 1.0f;
}

void Transform::SetRotation(CXMVECTOR vecRotation)
{
	m_vecRot = vecRotation;
	m_vecRot.m128_f32[3] = 1.0f;
}

void Transform::SetPosition(CXMVECTOR vecPosition)
{
	m_vecPos = vecPosition;
	m_vecPos.m128_f32[3] = 1.0f;
}

void Transform::AddPosition(CXMVECTOR vecPosition)
{
	m_vecPos += vecPosition;
	m_vecPos.m128_f32[3] = 1.0f;
}

void Transform::AddScale(CXMVECTOR vecScale)
{
	m_vecScale += vecScale;
	m_vecScale.m128_f32[3] = 1.0f;
}

void Transform::AddRotation(CXMVECTOR vecRotation)
{
	m_vecRot += vecRotation;
	m_vecRot.m128_f32[3] = 1.0f;
}

void Transform::SetParent(Transform* pTransform)
{
	m_pParent = pTransform;
}
