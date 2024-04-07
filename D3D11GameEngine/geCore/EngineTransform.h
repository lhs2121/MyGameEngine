#pragma once

class EngineTransform
{
public:
	// constrcuter destructer
	EngineTransform();
	~EngineTransform();

	// delete Function
	EngineTransform(const EngineTransform& _Other) = delete;
	EngineTransform(EngineTransform&& _Other) noexcept = delete;
	EngineTransform& operator=(const EngineTransform& _Other) = delete;
	EngineTransform& operator=(EngineTransform&& _Other) noexcept = delete;

	void TransformUpdate();
private:
	float4 Position;
	float4 Scale;
	float4 Rotation;

	float4x4 PositionMat;
	float4x4 ScaleMat;
	float4x4 RotationMat;

	EngineTransform* ParentTransform = nullptr;
	EngineTransform* ChildTransform = nullptr;
};