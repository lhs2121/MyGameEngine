#pragma once
#include <CoreLib\EngineLevel.h>

// ���� :
class TestLevel : public EngineLevel
{
public:
	void Awake() override;
	void Update(float _Delta) override;
};

