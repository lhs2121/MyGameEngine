#pragma once

class TestActor : public EngineObject
{
public:
	void Awake() override;
	void Update(float _Delta) override;
	void SetColScale(float4 _Scale);
	void SetColType(ColType _Type);
protected:
	EngineSpriteRenderer* Renderer;
	EngineCollision* Col;

};

