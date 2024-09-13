#pragma once
#include "Object.h"


enum class ColType
{
	AABB2D,
	Circle2D,
};
class Renderer;
class  Colider2D : public Object
{
public:
	void Awake() override;
	void Update(float _deltaTime) override;
	void Release() override;
	void SetColType(ColType _Type) { colType = _Type; }
	bool Collision(Colider2D* _Other);

	bool isCollision = false;
	float left;
	float right;
	float top;
	float bottom;
	float radius;

	ColType colType = ColType::AABB2D;
private:
	bool AABB2DAABB2D(Colider2D* _Other) const;
	bool Circle2DCircle2D(Colider2D* _Other) const;
	bool AABB2DCircle2D(Colider2D* _Other);

	Renderer* debugRenderer;
};