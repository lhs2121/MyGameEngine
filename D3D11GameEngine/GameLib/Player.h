#pragma once

class Player : public Object
{
public:
	void Awake() override;
	void Update(float _deltaTime) override;
	void OnCollisionEnter(Colider* _Other) override;

	SpriteRenderer* pSpriteRenderer;
	Colider* pColider;
	RigidBody* pRigid;
protected:
};

