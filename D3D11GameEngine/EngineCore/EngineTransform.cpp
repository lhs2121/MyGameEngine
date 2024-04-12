#include "Pre.h"
#include "EngineTransform.h"

EngineTransform::EngineTransform()
{
}

EngineTransform::~EngineTransform()
{
}

void EngineTransform::TransformUpdate()
{
	ScaleMat.Scale(Scale);
	RotationMat.Rotation(Rotation);
	PositionMat.Position(Position);
	WorldMat = ScaleMat * RotationMat * PositionMat;
}

void EngineTransform::SetPos(float4 Value)
{
	Position = Value;
}

void EngineTransform::SetScale(float4 Value)
{
	Scale = Value;
}

void EngineTransform::SetRotation(float4 Value)
{
	Rotation = Value;
}

void EngineTransform::AddPos(float4 Value)
{
	Position += Value;
}

void EngineTransform::AddScale(float4 Value)
{
	Scale += Value;
}

void EngineTransform::AddRotation(float4 Value)
{
	Rotation += Value;
}

void EngineTransform::View(float4& EyePos, float4& EyeDir, float4& EyeUp)
{
	float4x4 RotMat;
	RotMat.View(EyePos, EyeDir, EyeUp);

	float4x4 PosMat;
	PosMat.Position(-EyePos);
	ViewMat = RotMat * PosMat;
}