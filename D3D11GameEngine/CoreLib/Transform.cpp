#include "Pre.h"
#include "Transform.h"

void Transform::TransformUpdate()
{
	for (Transform* childTransform: childTransformList)
	{
		childTransform->scale = scale * localScale;
		childTransform->rotation = rotation + localRotation;
		childTransform->position = position + localPosition;
		childTransform->TransformUpdate();
	}

	worldScale = scale * localScale;
	worldRotation = rotation + localRotation;
	worldPosition = position + localPosition;

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

void Transform::SetlocalScale(float4 _scale)
{
	localScale = _scale;
	TransformUpdate();
}

void Transform::SetlocalRotation(float4 _rotation)
{
	localRotation = _rotation;
	TransformUpdate();
}

void Transform::AddLocalPos(float4 _pos)
{
	localPosition += _pos;
	TransformUpdate();
}

void Transform::AddlocalScale(float4 _scale)
{
	localScale += _scale;
	TransformUpdate();
}

void Transform::AddlocalRotation(float4 _rotation)
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

