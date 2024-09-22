#pragma once

class Player : public Object
{
public:
	void Awake() override;
	void Update(float _deltaTime) override;

	SpriteRenderer* pSpriteRenderer;
	Colider* pColider;
	RigidBody2D* pRigid;
protected:
};

