#pragma once
#include "Object.h"
enum class ColType
{
	AABB2D,
	AABB3D,
	OBB2D,
	OBB3D,
	SPHERE2D,
	SPHERE3D
};

class Renderer;
class  Colider : public Object
{
public:
	void Awake() override;
	void Update(float _deltaTime) override;
	void Release() override;

	void SetColType(ColType _Type);
	bool IsCollision() const { return isCollision; }

	bool Collision(Colider* _Other);
	Colider* opponent = nullptr;
private:
	bool AABB2DAABB2D(Colider* _Other) const;
	bool SPHERE2DSPHERE2D(Colider* _Other) const;
	bool AABB2DSPHERE2D(Colider* _Other);

	float left;
	float right;
	float top;
	float bottom;
	float radius;
	bool isCollision = false;
	ColType colType = ColType::AABB2D;
	Renderer* debugRenderer;
};