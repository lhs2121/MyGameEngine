#pragma once

class Player : public InputObject
{
public:
	void Awake() override;
	void Update(float _deltaTime) override;

protected:
	SpriteRenderer* pSpriteRenderer;
	Colider2D* pColider2D;
	RigidBody2D* pRigid;
};

