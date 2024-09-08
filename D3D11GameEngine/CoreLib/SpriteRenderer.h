#pragma once
#include "Renderer.h"

struct SpriteData
{
	float2 ResizeRatio = { 1.0f,1.0f };
	float2 Offset = { 0.0f,0.0f };
};

class  SpriteRenderer : public Renderer
{
public:
	~SpriteRenderer();

	void Awake() override;
	void Update(float _deltaTime) override;
	void Render() override;

	void CreateAnimation(int _SpriteCountX, int _SpriteCountY, float _InterTime);
private:
	int spriteCountX;
	int spriteCountY;

	int curSpriteX;
	int curSpriteY;

	int curFrame;

	float interTime = 0.05f;
	float curTime;

	SpriteData** ppSpriteDatas = nullptr;
	SpriteData curSpriteData;
	IConstantBuffer* pSpriteDataBuffer = nullptr;
};


