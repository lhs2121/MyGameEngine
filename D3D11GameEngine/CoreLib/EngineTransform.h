#pragma once
#include <BaseLib\BaseAPI.h>

class CoreAPI EngineTransform
{
public:
	void SetWorldViewProjection(float4x4& ViewMat, float4x4& ProjectionMat);
	void SetPos(float4 Value);
	void SetScale(float4 Value);
	void SetRotation(float4 Value);

	void AddPos(float4 Value);
	void AddScale(float4 Value);
	void AddRotation(float4 Value);

	void SetParent(EngineTransform* _Parent)
	{
		Parent = _Parent;
	}

	void SetChild(EngineTransform* _Child)
	{
		Child = _Child;
		Child->SetParent(this);
	}

	void TransformUpdate();

	float4 Position;
	float4 Scale = { 1,1,1,1 };
	float4 Rotation;

	float4x4 PositionMat;
	float4x4 ScaleMat;
	float4x4 RotationMat;

	float4x4 WorldMat;
	float4x4 ViewMat;
	float4x4 ProjectionMat;

	float4x4 WorldViewProjectionMat;

private:
	EngineTransform* Parent = nullptr;
	EngineTransform* Child  = nullptr;
};