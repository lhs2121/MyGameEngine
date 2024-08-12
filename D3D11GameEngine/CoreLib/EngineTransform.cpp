#include "Pre.h"
#include "EngineTransform.h"

void EngineTransform::TransformUpdate()
{
	//로컬 좌표계산하기전에 
	int Count = ChildTransform.GetCount();
	ChildTransform.GoFirst();
	for (size_t i = 0; i < Count; i++)
	{
		EngineTransform* TransformData = (EngineTransform*)ChildTransform.Item();
		TransformData->Scale = Scale;
		TransformData->Rotation = Rotation;
		TransformData->Position = Position;
		TransformData->TransformUpdate();
		ChildTransform.GoNext();
	}

	Scale *= LocalScale;
	Rotation += LocalRotation;
	Position += LocalPosition;

	ScaleMat.Scale(Scale);
	RotationMat.Rotation(Rotation);
	PositionMat.Position(Position);

	WorldMat.Identity();
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

