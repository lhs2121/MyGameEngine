#pragma once
#include "EngineObject.h"

enum class ColType
{
	AABB2D,
	Circle2D,
};
class EngineRenderer;
class  EngineCollision : public EngineObject
{
public:
	void Awake() override;
	void Update(float _Delta) override;

	void SetColType(ColType _Type) { Type = _Type; }
	void SetColScale(float4 _Scale);

	bool Collision(EngineCollision* _Other);

	bool AABB2DAABB2D(EngineCollision* _Other);
	bool Circle2DCircle2D(EngineCollision* _Other);
	bool AABB2DCircle2D(EngineCollision* _Other);

	bool IsCollision = false;
	float left;
	float right;
	float top;
	float bottom;
	float Radius;
	float4 ColScale;
	ColType Type = ColType::AABB2D;
private:
	EngineRenderer* DebugRenderer;
};