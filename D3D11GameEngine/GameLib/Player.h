#pragma once

class Player : public Object
{
public:
	~Player();
	void Awake() override;
	void Update(float _deltaTime) override;
	void OnCollisionEnter(Colider* _Other) override;

	ISpriteObject* pSp;
	ISpriteObject* pSp2;
protected:
};

