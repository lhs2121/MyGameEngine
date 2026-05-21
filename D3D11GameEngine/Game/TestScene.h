#pragma once

class TestScene : public Scene
{
public:
	~TestScene();

	void Awake() override;
	void Update(float _deltaTime) override;
	ISpriteObject* sprite = nullptr;
};

