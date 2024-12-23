#include "pch.h"
#include "Transform.h"

void Transform::TransformUpdate()
{
	m_vecWorldScale = m_vecRecievedScale * m_vecLocalScale;
	m_vecWorldRotation = m_vecRecievedRotation + m_vecLocalRotation;
	m_vecWorldPosition = m_vecRecievedPosition + m_vecLocalPosition;

	for (Transform* pTransform : m_pChildTransformList)
	{
		pTransform->m_vecRecievedScale = m_vecWorldScale;
		pTransform->m_vecRecievedRotation = m_vecWorldRotation;
		pTransform->m_vecRecievedPosition = m_vecWorldPosition;

		pTransform->TransformUpdate();
	}

	m_matWorldScale = XMMatrixScalingFromVector(m_vecWorldScale);
	m_matWorldRotation = XMMatrixRotationRollPitchYawFromVector(m_vecWorldRotation);
	m_matWorldPosition = XMMatrixTranslationFromVector(m_vecWorldPosition);
	m_quatWorld = XMQuaternionRotationMatrix(m_matWorldRotation);
	m_matWorld = m_matWorldScale * m_matWorldRotation * m_matWorldPosition;
}


void Transform::SetLocalScale(CXMVECTOR vecScale)
{
	m_vecLocalScale = vecScale;
	TransformUpdate();
}

void Transform::SetLocalRotation(CXMVECTOR vecRotation)
{
	m_vecLocalRotation = vecRotation;
	TransformUpdate();
}

void Transform::SetLocalPosition(CXMVECTOR vecPosition)
{
	m_vecLocalPosition = vecPosition;
	TransformUpdate();
}

void Transform::AddLocalPosition(CXMVECTOR vecPosition)
{
	m_vecLocalPosition += vecPosition;
	TransformUpdate();
}

void Transform::AddLocalScale(CXMVECTOR vecScale)
{
	m_vecLocalScale += vecScale;
	TransformUpdate();
}

void Transform::AddLocalRotation(CXMVECTOR vecRotation)
{
	m_vecLocalRotation += vecRotation;
	TransformUpdate();
}

void Transform::SetParent(Transform* pParent)
{
	if (m_pParent != nullptr)
	{
		m_pParent->m_pChildTransformList.remove(this);
	}
	m_pParent = pParent;
	m_pParent->m_pChildTransformList.push_back(this);
}
