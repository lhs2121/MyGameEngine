#include "Pre.h"
#include "Transform.h"

void Transform::TransformUpdate()
{
	vecWorldScale = vecRecievedScale * vecLocalScale;
	vecWorldRotation = vecRecievedRotation + vecLocalRotation;
	vecWorldPosition = vecRecievedPosition + vecLocalPosition;

	for (Transform* chTransform: childList)
	{
		chTransform->vecRecievedScale = vecWorldScale;
		chTransform->vecRecievedRotation = vecWorldRotation;
		chTransform->vecRecievedPosition = vecWorldPosition;

		chTransform->TransformUpdate();
	}

	matWorldScale = XMMatrixScalingFromVector(vecWorldScale);
	matWorldRotation = XMMatrixRotationRollPitchYawFromVector(vecWorldRotation);
	matWorldPosition = XMMatrixTranslationFromVector(vecWorldPosition);
	quatWorld = XMQuaternionRotationMatrix(matWorldRotation);
	matWorld = matWorldScale * matWorldRotation * matWorldPosition;
}

void Transform::SetWorldViewProjection(CXMMATRIX _matView, CXMMATRIX _matProjection)
{
	matWorldViewProjection = matWorld * _matView * _matProjection;
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

void Transform::SetParent(Transform* _parent)
{
	if (parent != nullptr)
	{
		parent->childList.remove(this);
	}
	parent = _parent;
	parent->childList.push_back(this);
}
