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
		delete SpriteDatas;
		SpriteDatas = nullptr;
	}
}

void EngineSpriteRenderer::Start()
{
	EngineRenderer::Start(); 

	{
		D3D11_BUFFER_DESC Desc = { 0 };
		Desc.Usage = D3D11_USAGE_DYNAMIC;
		Desc.ByteWidth = sizeof(SpriteData);
		Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		Desc.MiscFlags = 0;
		Desc.StructureByteStride = 0;

		HRESULT hr = EngineCore::GetDevice()->CreateBuffer(&Desc, nullptr, &SpriteDataBuffer);
	}
}

void EngineSpriteRenderer::Update(float _Delta)
{
	UpdateSpriteData(_Delta);
}

void EngineSpriteRenderer::Render()
{
	BindSpriteData();
	EngineRenderer::Render();
} 

void EngineSpriteRenderer::CreateAnimation(int _SpriteCountX, int _SpriteCountY, float _InterTime)
{
	if (CurTexture == nullptr)
	{
		EngineDebug::MsgBoxAssert("애니메이션을 만들기 전에 텍스처를 설정하세요");
	}

	SpriteCountX = _SpriteCountX;
	SpriteCountY = _SpriteCountY;

	SpriteDatas = new std::vector<std::vector<SpriteData>>(SpriteCountY, std::vector<SpriteData>(SpriteCountX));

	float2 Ratio = { 1 / static_cast<float>(SpriteCountX), 1 / static_cast<float>(SpriteCountY) };

	for (int y = 0; y < SpriteCountY; y++)
	{
		for (int x = 0; x < SpriteCountX; x++)
		{
			SpriteData& a = (*SpriteDatas)[y][x];
			a.ResizeRatio = Ratio;
			a.Offset.x = Ratio.x * x;
			a.Offset.y = Ratio.y * y;
		}
	}

	CurSpriteX = 0;
	CurSpriteY = 0;
	CurFrame = 0;
	CurTime = 0.0f;
	CurSpriteData = &(*SpriteDatas)[0][0];

	InterTime = _InterTime;
}

void EngineSpriteRenderer::UpdateSpriteData(float _Delta)
{
	CurTime += _Delta;
	if (CurTime >= InterTime)
	{
		CurSpriteData = &(*SpriteDatas)[CurSpriteY][CurSpriteX];

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
}

void EngineSpriteRenderer::BindSpriteData()
{
	D3D11_MAPPED_SUBRESOURCE MappedRes;

	EngineCore::GetContext()->Map(SpriteDataBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedRes);
	memcpy_s(MappedRes.pData, sizeof(SpriteData), CurSpriteData, sizeof(SpriteData));

	EngineCore::GetContext()->Unmap(SpriteDataBuffer, 0);
	EngineCore::GetContext()->PSSetConstantBuffers(1, 1, &SpriteDataBuffer);
}

