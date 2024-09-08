#pragma once

class TestActor : public Object
{
public:
	void Awake() override;
	void Update(float _Delta) override;
	void SetColScale(float4 _Scale);
	void SetColType(ColType _Type);
protected:
	SpriteRenderer* m_pSpriteRenderer;
	Colider2D* m_pColider2D;

};

