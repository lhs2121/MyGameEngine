#include "Pre.h"
#include "EngineTransform.h"

void EngineTransform::TransformUpdate()
{
	//로컬 좌표계산하기전에 
	UINT Count = ChildTransform.GetCount();
	ChildTransform.GoFirst();
	for (UINT i = 0; i < Count; i++)
	{
		EngineTransform* ChildTransformData = (EngineTransform*)ChildTransform.Item();
		ChildTransformData->Scale = Scale * LocalScale;
		ChildTransformData->Rotation = Rotation + LocalRotation;
		ChildTransformData->Position = Position + LocalPosition;
		ChildTransformData->TransformUpdate();
		ChildTransform.GoNext();
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

