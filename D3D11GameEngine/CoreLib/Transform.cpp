#include "Pre.h"
#include "Transform.h"

void Transform::TransformUpdate()
{
	for (Transform* ChildTransform: ChildTransformList)
	{
		ChildTransform->Scale = Scale * LocalScale;
		ChildTransform->Rotation = Rotation + LocalRotation;
		ChildTransform->Position = Position + LocalPosition;
		ChildTransform->TransformUpdate();
	}

	WorldScale = Scale * LocalScale;
	WorldRotation = Rotation + LocalRotation;
	WorldPosition = Position + LocalPosition;

	ScaleMat.Scale(WorldScale);
	RotationMat.Rotation(WorldRotation);
	PositionMat.Position(WorldPosition);

	WorldMat.Identity();
	WorldMat = ScaleMat * RotationMat * PositionMat;
}

void Transform::SetWorldViewProjection(float4x4& ViewMat, float4x4& ProjectionMat)
{
}

void Transform::SetLocalPos(float4 Value)
{
	LocalPosition = Value;
	TransformUpdate();
}

void Transform::SetLocalScale(float4 Value)
{
	LocalScale = Value;
	TransformUpdate();
}

void Transform::SetLocalRotation(float4 Value)
{
	LocalRotation = Value;
	TransformUpdate();
}

void Transform::AddLocalPos(float4 Value)
{
	LocalPosition += Value;
	TransformUpdate();
}

void Transform::AddLocalScale(float4 Value)
{
	LocalScale += Value;
	TransformUpdate();
}

void Transform::AddLocalRotation(float4 Value)
{
	LocalRotation += Value;
	TransformUpdate();
}

void Transform::SetPos(float4 Value)
{
	Position = Value;
	TransformUpdate();
}

void Transform::SetScale(float4 Value)
{
	Scale = Value;
	TransformUpdate();
}

void Transform::SetRotation(float4 Value)
{
	Rotation = Value;
	TransformUpdate();
}

void Transform::AddPos(float4 Value)
{
	Position += Value;
	TransformUpdate();
}

void Transform::AddScale(float4 Value)
{
	Scale += Value;
	TransformUpdate();
}

void Transform::AddRotation(float4 Value)
{
	Rotation += Value;
	TransformUpdate();
}

