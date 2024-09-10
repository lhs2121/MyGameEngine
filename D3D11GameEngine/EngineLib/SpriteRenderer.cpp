#include "Pre.h"
#include "SpriteRenderer.h"

SpriteRenderer::~SpriteRenderer()
{
	if (ppSpriteDatas != nullptr)
	{
		for (int i = 0; i < spriteCountY; i++)
		{
			delete[] ppSpriteDatas[i];
			ppSpriteDatas[i] = nullptr;
		}
		delete[] ppSpriteDatas;
		ppSpriteDatas = nullptr;
	}
}

void SpriteRenderer::Awake()
{
	Renderer::Awake();
}

void SpriteRenderer::Update(float _deltaTime)
{
	curTime += _deltaTime;
	if (curTime >= interTime)
	{
		curSpriteData = ppSpriteDatas[curSpriteY][curSpriteX];

		curSpriteX++;
		curFrame++;
		curTime = 0.0f;
	}

	if (curSpriteX == spriteCountX)
	{
		curSpriteY++;
		curSpriteX = 0;
	}

	if (curSpriteY == spriteCountY)
	{
		curSpriteY = 0;
		curFrame = 0;
	}
}

void SpriteRenderer::Render()
{
	pSpriteDataBuffer->IntoPipeline(ShaderType::PS, 5);
	Renderer::Render();
}

void SpriteRenderer::SetTexture(const char* _name)
{
	ITexture* texture = (ITexture*)mainResManager->Find(ResType::Texture, _name);
	pMaterial->SetTexture(_name);

	float4 imageScale = texture->GetImageScale();
	transform.SetlocalScale(imageScale);
}

void SpriteRenderer::CreateAnimation(int _SpriteCountX, int _SpriteCountY, float _InterTime)
{
	ppSpriteDatas = new SpriteData * [_SpriteCountY];

	for (int i = 0; i < _SpriteCountY; i++)
	{
		ppSpriteDatas[i] = new SpriteData[_SpriteCountX];
	}

	spriteCountX = _SpriteCountX;
	spriteCountY = _SpriteCountY;


	float2 Ratio = { 1 / static_cast<float>(spriteCountX), 1 / static_cast<float>(spriteCountY) };

	for (int y = 0; y < spriteCountY; y++)
	{
		for (int x = 0; x < spriteCountX; x++)
		{
			SpriteData& Data = ppSpriteDatas[y][x];

			Data.ResizeRatio = Ratio;
			Data.Offset.x = Ratio.x * x;
			Data.Offset.y = Ratio.y * y;
		}
	}

	curSpriteX = 0;
	curSpriteY = 0;
	curFrame = 0;
	curTime = 0.0f;
	curSpriteData = ppSpriteDatas[0][0];
	interTime = _InterTime;

	static int SpriteDataBufferCount = 0;
	EngineString BufferName = "SpriteData_";
	BufferName += SpriteDataBufferCount;
	SpriteDataBufferCount++;
	pSpriteDataBuffer = (IConstantBuffer*)mainResManager->CreateResource(ResType::CB, BufferName);
	pSpriteDataBuffer->Setting(&curSpriteData, sizeof(SpriteData));
}


