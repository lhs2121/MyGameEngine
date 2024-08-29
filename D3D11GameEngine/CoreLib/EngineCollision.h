#pragma once
#include "EngineComponent.h"

enum class Colype
{
	Rect,
	Circle,
};
class CoreAPI EngineCollision : public EngineComponent
{
public:
	void Awake() override;
	void Update(float _Delta) override;
	bool AABB(EngineCollision* _Other);

	float left;
	float right;
	float top;
	float bottom;
	float4 ColScale = { 100,100 };
	Colype Type = Colype::Rect;
};