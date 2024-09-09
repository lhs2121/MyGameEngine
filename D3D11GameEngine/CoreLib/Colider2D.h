#pragma once
#include "Object.h"
#include "Component.h"

enum class ColType
{
	AABB2D,
	Circle2D,
};
class Renderer;
class  Colider2D : public Component
{
public:
	void Awake() override;
	void Update(float _deltaTime) override;

	void SetColType(ColType _Type) { colType = _Type; }
	void SetColScale(float4 _Scale);

	bool Collision(Colider2D* _Other);

	bool isCollision = false;
	float left;
	float right;
	float top;
	float bottom;
	float radius;
	float4 colScale;
private:
	bool AABB2DAABB2D(Colider2D* _Other) const;
	bool Circle2DCircle2D(Colider2D* _Other) const;
	bool AABB2DCircle2D(Colider2D* _Other);

	ColType colType = ColType::AABB2D;
	Renderer* debugRenderer;
};