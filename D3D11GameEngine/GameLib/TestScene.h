#pragma once

// ���� :
class Player;
class TestScene : public Scene
{
public:
	void Awake() override;
	void Update(float _deltaTime) override;

	Player* a = nullptr;
};

