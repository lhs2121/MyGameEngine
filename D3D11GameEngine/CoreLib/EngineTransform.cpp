#include "Pre.h"
#include "EngineTransform.h"

void EngineTransform::TransformUpdate()
{
	for (EngineTransform* ChildTransform: ChildTransformList)
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

void EngineTransform::SetWorldViewProjection(float4x4& ViewMat, float4x4& ProjectionMat)
{
}

void EngineTransform::SetLocalPos(float4 Value)
{
	LocalPosition = Value;
	TransformUpdate();
}

void EngineTransform::SetLocalScale(float4 Value)
{
	LocalScale = Value;
	TransformUpdate();
}

void EngineTransform::SetLocalRotation(float4 Value)
{
	LocalRotation = Value;
	TransformUpdate();
}

void EngineTransform::AddLocalPos(float4 Value)
{
	LocalPosition += Value;
	TransformUpdate();
}

void EngineTransform::AddLocalScale(float4 Value)
{
	LocalScale += Value;
	TransformUpdate();
}

void EngineTransform::AddLocalRotation(float4 Value)
{
	LocalRotation += Value;
	TransformUpdate();
}

void EngineTransform::SetPos(float4 Value)
{
	Position = Value;
	TransformUpdate();
}

void EngineTransform::SetScale(float4 Value)
{
	Scale = Value;
	TransformUpdate();
}

void EngineTransform::SetRotation(float4 Value)
{
	Rotation = Value;
	TransformUpdate();
}

void EngineTransform::AddPos(float4 Value)
{
	Position += Value;
	TransformUpdate();
}

void EngineTransform::AddScale(float4 Value)
{
	Scale += Value;
	TransformUpdate();
}

void EngineTransform::AddRotation(float4 Value)
{
	Rotation += Value;
	TransformUpdate();
}

