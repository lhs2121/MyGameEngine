#pragma once
#include <BaseLib\BaseAPI.h>

class CoreAPI EngineTransform
{
public:
	void SetWorldViewProjection(float4x4& ViewMat, float4x4& ProjectionMat);

	void SetLocalPos(float4 Value);
	void SetLocalScale(float4 Value);
	void SetLocalRotation(float4 Value);

	void AddLocalPos(float4 Value);
	void AddLocalScale(float4 Value);
	void AddLocalRotation(float4 Value);

	void SetPos(float4 Value);
	void SetScale(float4 Value);
	void SetRotation(float4 Value);

	void AddPos(float4 Value);
	void AddScale(float4 Value);
	void AddRotation(float4 Value);

	void TransformUpdate();

	float4 LocalScale = { 1.0f,1.0f,1.0f,1.0f };
	float4 LocalRotation;
	float4 LocalPosition;

	float4 Scale = { 1.0f,1.0f,1.0f,1.0f };
	float4 Rotation;
	float4 Position;

	float4 WorldScale = { 1.0f,1.0f,1.0f,1.0f };
	float4 WorldRotation;
	float4 WorldPosition;

	float4x4 ScaleMat;
	float4x4 RotationMat;
	float4x4 PositionMat;

	float4x4 WorldMat;
	float4x4 ViewMat;
	float4x4 ProjectionMat;

	float4x4 WorldViewProjectionMat;

	EngineTransform* ParentTransform = nullptr;
	EngineList ChildTransform;
};