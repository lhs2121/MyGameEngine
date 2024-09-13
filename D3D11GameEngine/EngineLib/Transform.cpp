#include "Pre.h"
#include "Transform.h"

void Transform::TransformUpdate()
{
	worldScale = scale * localScale;
	worldRotation = rotation + localRotation;
	worldPosition = position + localPosition;

	for (Transform* childTransform: childTransformList)
	{
		childTransform->scale = worldScale;
		childTransform->rotation = worldRotation;
		childTransform->position = worldPosition;
		childTransform->TransformUpdate();
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

void Transform::SetPos(float4 _pos)
{
	position = _pos;
	TransformUpdate();
}

void Transform::SetScale(float4 _scale)
{
	scale = _scale;
	TransformUpdate();
}

void Transform::SetRotation(float4 _rotation)
{
	rotation = _rotation;
	TransformUpdate();
}

void Transform::AddPos(float4 _pos)
{
	position += _pos;
	TransformUpdate();
}

void Transform::AddScale(float4 _scale)
{
	scale += _scale;
	TransformUpdate();
}

void Transform::AddRotation(float4 Value)
{
	rotation += Value;
	TransformUpdate();
}

void Transform::SetParent(Transform* _parentTransform)
{
	if (parentTransform != nullptr)
	{
		parentTransform->childTransformList.remove(this);
	}
	parentTransform = _parentTransform;
	parentTransform->childTransformList.push_back(this);
}
