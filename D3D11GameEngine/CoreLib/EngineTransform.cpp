#include "Pre.h"
#include "EngineTransform.h"

void EngineTransform::TransformUpdate()
{
	WorldMat.Identity();

	ScaleMat.Scale(Scale);
	RotationMat.Rotation(Rotation);
	PositionMat.Position(Position);

	WorldMat = ScaleMat * RotationMat * PositionMat;
}

void EngineTransform::SetWorldViewProjection(float4x4& ViewMat, float4x4& ProjectionMat)
{
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
