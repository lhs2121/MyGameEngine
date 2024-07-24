#pragma once
#include <CoreLib\CoreAPI.h>
#include <CoreLib\EngineActor.h>

class EngineSpriteRenderer;
class TestActor : public EngineActor
{
public:
	void Awake() override;
	void Update(float _Delta) override;
protected:
	EngineSpriteRenderer* Renderer;

};

