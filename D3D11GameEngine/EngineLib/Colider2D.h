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

	void SetColType(ColType _Type);
	bool IsCollision() const { return isCollision; }

	bool Collision(Colider2D* _Other);
	float4 dir;
private:
	bool AABB2DAABB2D(Colider2D* _Other) const;
	bool Circle2DCircle2D(Colider2D* _Other) const;
	bool AABB2DCircle2D(Colider2D* _Other);

	float left;
	float right;
	float top;
	float bottom;
	float radius;
	bool isCollision = false;
	ColType colType = ColType::AABB2D;
	Renderer* debugRenderer;
};