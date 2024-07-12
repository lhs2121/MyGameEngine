#pragma once
#include "EngineRenderer.h"

struct SpriteData
{
	float2 ResizeRatio = { 1.0f,1.0f };
	float2 Offset = { 0.0f,0.0f };
};

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
	void Update(float _Delta) override;
	void Render() override;

	void CreateAnimation(int _SpriteCountX, int _SpriteCountY, float _InterTime);
private:
	int SpriteCountX;
	int SpriteCountY;

	int CurSpriteX;
	int CurSpriteY;

	int CurFrame;

	float InterTime = 0.05f;
	float CurTime;

	SpriteData** SpriteDatas = nullptr;
	SpriteData CurSpriteData;
	IEngineConstantBuffer* SpriteDataBuffer = nullptr;
};


