#pragma once

// Ό³Έν :
class Player;
class TestLevel : public Level
{
public:
	void Awake() override;
	void Update(float _deltaTime) override;

	Player* a = nullptr;
	Player* b = nullptr;
	Player* c = nullptr;
	Player* d = nullptr;
};

