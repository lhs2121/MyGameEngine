#include "Pre.h"
#include "Transform.h"

void Transform::TransformUpdate()
{
	worldScale = scale * localScale;
	worldRotation = rotation + localRotation;
	worldPosition = position + localPosition;

	for (Transform* child: childList)
	{
		child->scale = worldScale;
		child->rotation = worldRotation;
		child->position = worldPosition;
		child->TransformUpdate();
	}

	scaleMat = XMMatrixIdentity();
	scaleMat = XMMatrixScalingFromVector(worldScale);

	rotationMat = XMMatrixIdentity();
	rotationMat = XMMatrixRotationRollPitchYawFromVector(worldRotation);

	positionMat = XMMatrixIdentity();
	positionMat = XMMatrixTranslationFromVector(worldPosition);

	worldQuaternion =  XMQuaternionRotationMatrix(rotationMat);

	worldMat = XMMatrixIdentity();
	worldMat = scaleMat * rotationMat * positionMat;
}

void Transform::SetWorldViewProjection(CXMMATRIX matView, CXMMATRIX matProjection)
{
	XMMATRIX matViewProjection = XMMatrixMultiply(matView, matProjection);
	worldViewProjectionMat = XMMatrixMultiply(worldMat, matViewProjection);
}

void Transform::SetLocalPos(CXMVECTOR _pos)
{
	localPosition = _pos;
	TransformUpdate();
}

void Transform::SetLocalScale(CXMVECTOR _scale)
{
	localScale = _scale;
	TransformUpdate();
}

void Transform::SetLocalRotation(CXMVECTOR _rotation)
{
	localRotation = _rotation;
	TransformUpdate();
}

void Transform::AddLocalPos(CXMVECTOR _pos)
{
	localPosition += _pos;
	TransformUpdate();
}

void Transform::AddLocalScale(CXMVECTOR _scale)
{
	localScale += _scale;
	TransformUpdate();
}

void Transform::AddLocalRotation(CXMVECTOR _rotation)
{
	localRotation += _rotation;
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
