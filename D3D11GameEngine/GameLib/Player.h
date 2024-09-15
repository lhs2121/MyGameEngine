#pragma once

class Player : public InputObject
{
public:
	void Awake() override;
	void Update(float _deltaTime) override;

	SpriteRenderer* pSpriteRenderer;
	Colider2D* pColider2D;
	RigidBody2D* pRigid;
protected:
};

