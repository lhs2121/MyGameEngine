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

	void TransformUpdate();

	float4 LocalPosition = { 0,0,0,1 };
	float4 LocalScale = { 1,1,1,1 };
	float4 LocalRotation = { 0,0,0,1 };;

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

	EngineTransform* ParentTransform = nullptr;
	EngineList ChildTransform;
};