#pragma once

class Player : public GameObject
{
public:
	void Awake() override;
	void Update(float _deltaTime) override;

protected:
	SpriteRenderer* pSpriteRenderer;
	Colider2D* pColider2D;
};

