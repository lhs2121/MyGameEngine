#pragma once

class Ground : public Object
{
public:
	void Awake() override;
	void Update(float _deltaTime) override;

	SpriteRenderer* pSpriteRenderer;
	Colider* pColider;
protected:
};

