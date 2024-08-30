#pragma once

class EngineSpriteRenderer;
class TestActor : public EngineActor
{
public:
	void Awake() override;
	void Update(float _Delta) override;
	void SetColScale(float4 _Scale);
protected:
	EngineSpriteRenderer* Renderer;
	EngineCollision* Col;

};

