#include "Pre.h"
#include "EngineSpriteRenderer.h"
#include "Singleton.h"

EngineSpriteRenderer::~EngineSpriteRenderer()
{
	if (SpriteDatas != nullptr)
	{
		for (size_t i = 0; i < SpriteCountY; i++)
		{
			delete[] SpriteDatas[i];
			SpriteDatas[i] = nullptr;
		}
		delete[] SpriteDatas;
		SpriteDatas = nullptr;
	}
}

void EngineSpriteRenderer::Awake()
{
	EngineRenderer::Awake();
}

void EngineSpriteRenderer::Update(float _Delta)
{
	CurTime += _Delta;
	if (CurTime >= InterTime)
	{
		CurSpriteData = SpriteDatas[CurSpriteY][CurSpriteX];

		CurSpriteX++;
		CurFrame++;
		CurTime = 0.0f;
	}

	if (CurSpriteX == SpriteCountX)
	{
		CurSpriteY++;
		CurSpriteX = 0;
	}

	if (CurSpriteY == SpriteCountY)
	{
		CurSpriteY = 0;
		CurFrame = 0;
	}

	SpriteDataBuffer->IntoPipeline(ShaderType::PS, 5);
}

void EngineSpriteRenderer::Render()
{
	EngineRenderer::Render();
} 
 
void EngineSpriteRenderer::CreateAnimation(int _SpriteCountX, int _SpriteCountY, float _InterTime)
{
	SpriteDatas = new SpriteData * [_SpriteCountY];

	for (size_t i = 0; i < _SpriteCountY; i++)
	{
		SpriteDatas[i] = new SpriteData[_SpriteCountX];
	}

	SpriteCountX = _SpriteCountX;
	SpriteCountY = _SpriteCountY;


	float2 Ratio = { 1 / static_cast<float>(SpriteCountX), 1 / static_cast<float>(SpriteCountY) };

	for (int y = 0; y < SpriteCountY; y++)
	{
		for (int x = 0; x < SpriteCountX; x++)
		{
			SpriteData& Data = SpriteDatas[y][x];

			Data.ResizeRatio = Ratio;
			Data.Offset.x = Ratio.x * x;
			Data.Offset.y = Ratio.y * y;
		}
	}

	CurSpriteX = 0;
	CurSpriteY = 0;
	CurFrame = 0;
	CurTime = 0.0f;
	CurSpriteData = SpriteDatas[0][0];

	InterTime = _InterTime;

	
	SpriteDataBuffer = (IEngineConstantBuffer*)MainD3DManager->CreateResource(ResType::CB, "SpriteData");
	SpriteDataBuffer->Setting(&CurSpriteData, sizeof(SpriteData));
}


