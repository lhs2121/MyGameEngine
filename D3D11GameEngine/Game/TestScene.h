#pragma once

class TestScene : public Scene
{
public:
	void Awake() override;
	void Update(float _deltaTime) override;
	ISpriteObject* sprite = nullptr;
};

