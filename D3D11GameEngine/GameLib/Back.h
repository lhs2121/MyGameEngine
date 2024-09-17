#pragma once

class Back : public Object
{
public:
	void Awake() override;
	void Update(float _deltaTime) override;

	SpriteRenderer* pSpriteRenderer;
protected:
};

