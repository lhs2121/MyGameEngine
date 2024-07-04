#include "Pre.h"
#include "EngineSpriteRenderer.h"

EngineSpriteRenderer::EngineSpriteRenderer()
{
}

EngineSpriteRenderer::~EngineSpriteRenderer()
{
	if (SpriteDataBuffer != nullptr)
	{
		SpriteDataBuffer->Release();
		SpriteDataBuffer = nullptr;
	}

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

void EngineSpriteRenderer::Start()
{
	EngineRenderer::Start(); 
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

	SpriteDataBuffer->IntoPipeLine(ShaderType::PS, 5);
}

void EngineSpriteRenderer::Render()
{

	EngineRenderer::Render();
} 
 
void EngineSpriteRenderer::CreateAnimation(int _SpriteCountX, int _SpriteCountY, float _InterTime)
{
	if (CurTexture == nullptr)
	{
		EngineDebug::MsgBoxAssert("애니메이션을 만들기 전에 텍스처를 설정하세요");
	}

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

	{
		D3D11_BUFFER_DESC Desc = { 0 };
		Desc.Usage = D3D11_USAGE_DYNAMIC;
		Desc.ByteWidth = sizeof(SpriteData);
		Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		Desc.MiscFlags = 0;
		Desc.StructureByteStride = 0;

		SpriteDataBuffer = EngineCore::GetMainD3DManager()->CreateConstantBuffer("SpriteData");
		SpriteDataBuffer->Setting(Desc, &CurSpriteData, sizeof(SpriteData));
	}
}


