#pragma once

// Ό³Έν :
class TestActor;
class TestLevel : public Level
{
public:
	void Awake() override;
	void Update(float _deltaTime) override;

	TestActor* a = nullptr;
	TestActor* b = nullptr;
	TestActor* c = nullptr;
	TestActor* d = nullptr;
};

