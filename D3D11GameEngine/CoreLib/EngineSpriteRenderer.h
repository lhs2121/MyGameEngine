#pragma once
#include "EngineRenderer.h"

struct SpriteData
{
	float2 ResizeRatio = { 1.0f,1.0f };
	float2 Offset = { 0.0f,0.0f };
};

class CoreAPI EngineSpriteRenderer : public EngineRenderer
{
public:
	~EngineSpriteRenderer();

	void Awake() override;
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
	IConstantBuffer* SpriteDataBuffer = nullptr;
};


