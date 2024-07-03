#pragma once
#include <EngineCore\EngineActor.h>
#include <EngineCore\EngineSpriteRenderer.h>

// Ό³Έν :
class TestActor : public EngineActor
{
public:
	// constrcuter destructer
	TestActor();
	~TestActor();

	// delete Function
	TestActor(const TestActor& _Other) = delete;
	TestActor(TestActor&& _Other) noexcept = delete;
	TestActor& operator=(const TestActor& _Other) = delete;
	TestActor& operator=(TestActor&& _Other) noexcept = delete;

	void Start() override;
	void Update(float _Delta) override;
protected:
	EngineSpriteRenderer* Renderer;

};

