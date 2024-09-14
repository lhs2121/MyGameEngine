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

	scaleMat.Scale(worldScale);
	rotationMat.Rotation(worldRotation);
	positionMat.Position(worldPosition);

	worldMat.Identity();
	worldMat = scaleMat * rotationMat * positionMat;
}

void Transform::SetWorldViewProjection(float4x4& _viewMat, float4x4& _projectionMat)
{
	worldViewProjectionMat = worldMat* _viewMat * _projectionMat;
}

void Transform::SetLocalPos(float4 _pos)
{
	localPosition = _pos;
	TransformUpdate();
}

void Transform::SetLocalScale(float4 _scale)
{
	localScale = _scale;
	TransformUpdate();
}

void Transform::SetLocalRotation(float4 _rotation)
{
	localRotation = _rotation;
	TransformUpdate();
}

void Transform::AddLocalPos(float4 _pos)
{
	localPosition += _pos;
	TransformUpdate();
}

void Transform::AddLocalScale(float4 _scale)
{
	localScale += _scale;
	TransformUpdate();
}

void Transform::AddLocalRotation(float4 _rotation)
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
