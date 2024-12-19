#include "pch.h"
#include "Transform.h"

void Transform::TransformUpdate()
{
	vecWorldScale = vecRecievedScale * vecLocalScale;
	vecWorldRotation = vecRecievedRotation + vecLocalRotation;
	vecWorldPosition = vecRecievedPosition + vecLocalPosition;

	for (Transform* child : childList)
	{
		child->vecRecievedScale = vecWorldScale;
		child->vecRecievedRotation = vecWorldRotation;
		child->vecRecievedPosition = vecWorldPosition;

		child->TransformUpdate();
	}

	matWorldScale = XMMatrixScalingFromVector(vecWorldScale);
	matWorldRotation = XMMatrixRotationRollPitchYawFromVector(vecWorldRotation);
	matWorldPosition = XMMatrixTranslationFromVector(vecWorldPosition);
	quatWorld = XMQuaternionRotationMatrix(matWorldRotation);
	matWorld = matWorldScale * matWorldRotation * matWorldPosition;
}

void Transform::SetLocalPosition(CXMVECTOR _pos)
{
	vecLocalPosition = _pos;
	TransformUpdate();
}

void Transform::SetLocalScale(CXMVECTOR _scale)
{
	vecLocalScale = _scale;
	TransformUpdate();
}

void Transform::SetLocalRotation(CXMVECTOR _rotation)
{
	vecLocalRotation = _rotation;
	TransformUpdate();
}

void Transform::AddLocalPosition(CXMVECTOR _pos)
{
	vecLocalPosition += _pos;
	TransformUpdate();
}

void Transform::AddLocalScale(CXMVECTOR _scale)
{
	vecLocalScale += _scale;
	TransformUpdate();
}

void Transform::AddLocalRotation(CXMVECTOR _rotation)
{
	vecLocalRotation += _rotation;
	TransformUpdate();
}

void Transform::SetParent(Transform* _m_pParent)
{
	if (m_pParent != nullptr)
	{
		m_pParent->childList.remove(this);
	}
	m_pParent = _m_pParent;
	m_pParent->childList.push_back(this);
}
