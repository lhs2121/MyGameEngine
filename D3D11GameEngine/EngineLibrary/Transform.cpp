#include "pch.h"
#include "Transform.h"

XMVECTOR Transform::ReadVector(std::initializer_list<float> value, float zDefault, float wDefault)
{
	float data[4] = { 0.0f, 0.0f, zDefault, wDefault };
	int index = 0;
	for (float element : value)
	{
		if (index >= 4)
			break;

		data[index] = element;
		++index;
	}

	return { data[0], data[1], data[2], data[3] };
}

void Transform::SetLocalPosition(std::initializer_list<float> value)
{
	m_vecLocalPosition = ReadVector(value, 0.0f, 1.0f);
}

void Transform::SetLocalScale(std::initializer_list<float> value)
{
	m_vecLocalScale = ReadVector(value, 1.0f, 1.0f);
}

void Transform::SetLocalRotation(std::initializer_list<float> value)
{
	m_vecLocalRotation = ReadVector(value, 0.0f, 1.0f);
}

void Transform::AddLocalPosition(std::initializer_list<float> value)
{
	m_vecLocalPosition = XMVectorAdd(m_vecLocalPosition, ReadVector(value, 0.0f, 0.0f));
	m_vecLocalPosition.m128_f32[3] = 1.0f;
}

void Transform::AddLocalRotation(std::initializer_list<float> value)
{
	m_vecLocalRotation = XMVectorAdd(m_vecLocalRotation, ReadVector(value, 0.0f, 0.0f));
	m_vecLocalRotation.m128_f32[3] = 1.0f;
}

void Transform::TransformUpdate()
{
	XMMATRIX matScale = XMMatrixScalingFromVector(m_vecLocalScale);
	XMMATRIX matRotation = XMMatrixRotationRollPitchYawFromVector(m_vecLocalRotation);
	XMMATRIX matPosition = XMMatrixTranslationFromVector(m_vecLocalPosition);

	m_matWorld = matScale * matRotation * matPosition;
	if (m_pParent != nullptr)
	{
		m_matWorld *= m_pParent->m_matWorld;
	}

	XMVECTOR unusedRotation;
	XMVECTOR unusedQuaternion;
	XMMatrixDecompose(&m_vecWorldScale, &unusedQuaternion, &m_vecWorldPosition, m_matWorld);
	m_vecWorldRotation = m_vecLocalRotation;
}
