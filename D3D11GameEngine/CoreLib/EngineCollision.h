#pragma once
#include "EngineComponent.h"

enum class Colype
{
	Rect,
	Circle,
};
class EngineCollision : public EngineComponent
{
	void Awake() override;
	void Update(float _Delta) override;

	float4 RectCorners;
	Colype Type = Colype::Rect;
};