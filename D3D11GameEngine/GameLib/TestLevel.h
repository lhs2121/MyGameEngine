#pragma once

// Ό³Έν :
class TestActor;
class TestLevel : public EngineLevel
{
public:
	void Awake() override;
	void Update(float _Delta) override;

	TestActor* a = nullptr;
	TestActor* b = nullptr;
	TestActor* c = nullptr;
	TestActor* d = nullptr;
};

