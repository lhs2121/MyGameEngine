#pragma once
#include "EngineComponent.h"

enum class ColType
{
	Rect,
	Circle,
};
class CoreAPI EngineCollision : public EngineComponent
{
public:
	void Awake() override;
	void Update(float _Delta) override;
	void SetColType(ColType _Type) { Type = _Type; }
	bool Collision(EngineCollision* _Other);
	bool AABB(EngineCollision* _Other);
	bool Circle(EngineCollision* _Other);
	bool AABBvsCircle(EngineCollision* _Other);

	bool IsCollision = false;
	float left;
	float right;
	float top;
	float bottom;
	float Radius;
	float4 ColScale = { 100,100 };
	ColType Type = ColType::Rect;
};