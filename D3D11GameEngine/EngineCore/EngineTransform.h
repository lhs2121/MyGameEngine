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
private:
	EngineTransform* Parent = nullptr;
	EngineTransform* Child = nullptr;

	float4 Position;
	float4 Scale;
	float4 Rotation;

	float4x4 PositionMat;
	float4x4 ScaleMat;
	float4x4 RotationMat;
	float4x4 WorldMat;
};