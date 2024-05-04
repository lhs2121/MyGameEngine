#pragma once
#include "EngineRenderer.h"

class EngineSpriteRenderer : public EngineRenderer
{
public:
	// constrcuter destructer
	EngineSpriteRenderer();
	~EngineSpriteRenderer();

	// delete Function
	EngineSpriteRenderer(const EngineSpriteRenderer& _Other) = delete;
	EngineSpriteRenderer(EngineSpriteRenderer&& _Other) noexcept = delete;
	EngineSpriteRenderer& operator=(const EngineSpriteRenderer& _Other) = delete;
	EngineSpriteRenderer& operator=(EngineSpriteRenderer&& _Other) noexcept = delete;

	void Start() override;
	void Render() override;
};


