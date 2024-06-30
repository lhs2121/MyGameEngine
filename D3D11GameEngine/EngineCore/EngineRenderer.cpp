#include "Pre.h"
#include "EngineRenderer.h"
#include "EngineCamera.h"

EngineRenderer::EngineRenderer()
{
}

EngineRenderer::~EngineRenderer()
{
	if (TransformBuffer != nullptr)
	{
		TransformBuffer->Release();
		TransformBuffer = nullptr;
	}

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

void EngineRenderer::Start()
{
	GetLevel()->GetMainCamera()->PushRenderer(this);

	{
		D3D11_BUFFER_DESC Desc = { 0 };
		Desc.Usage = D3D11_USAGE_DYNAMIC;
		Desc.ByteWidth = sizeof(float4x4);
		Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		Desc.MiscFlags = 0;
		Desc.StructureByteStride = 0;

		HRESULT hr = EngineCore::GetDevice()->CreateBuffer(&Desc, nullptr, &TransformBuffer);
	}


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

	IEngineD3DManager* Manager = EngineCore::GetMainD3DManager();

	VB = Manager->FindVertexBuffer("Box2DTex");
	IB = Manager->FindIndexBuffer("Box2D");
	IA = Manager->FindInputLayout("PosTexcoord");
	VS = Manager->FindVertexShader("TestSpriteShader");
	PS = Manager->FindPixelShader("TestSpriteShader");
	RS = Manager->FindRasterizer("Default");
	DS = Manager->FindDepthStencil("Default");

	BindSampler("Default");
}

void EngineRenderer::Update(float _Delta)
{
	BindTransform();

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

	BindSpriteData();

}
void EngineRenderer::Render()
{
	VB->IntoPipeLine();
	IB->IntoPipeLine();
	IA->IntoPipeLine();
	VS->IntoPipeLine();
	RS->IntoPipeLine();
	PS->IntoPipeLine();
	DS->IntoPipeLine();

	UINT IndexCount = IB->GetIndexCount();
	EngineCore::GetContext()->DrawIndexed(IndexCount, 0, 0);
}

void EngineRenderer::CreateAnimation(int _SpriteCountX, int _SpriteCountY)
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

}

void EngineRenderer::BindTexture(EngineString _Name)
{
	CurTexture = EngineCore::GetMainD3DManager()->FindTexture(_Name);

	float4 ImageScale = CurTexture->GetImageScale();
	Transform.SetScale(ImageScale);

	ID3D11ShaderResourceView* SRV = CurTexture->GetSRV();
	EngineCore::GetContext()->PSSetShaderResources(0, 1, &SRV);
}

void EngineRenderer::BindSampler(EngineString _Name)
{
	IEngineSampler* Sampler = EngineCore::GetMainD3DManager()->FindSampler(_Name);
	ID3D11SamplerState* State = Sampler->GetState();
	EngineCore::GetContext()->PSSetSamplers(0, 1, &State);
}

void EngineRenderer::BindTransform() 
{
	D3D11_MAPPED_SUBRESOURCE MappedRes;

	EngineCore::GetContext()->Map(TransformBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedRes);
	memcpy_s(MappedRes.pData, sizeof(float4x4), &Transform.WorldViewProjectionMat, sizeof(float4x4));

	EngineCore::GetContext()->Unmap(TransformBuffer, 0);
	EngineCore::GetContext()->VSSetConstantBuffers(0, 1, &TransformBuffer);
}

void EngineRenderer::BindSpriteData()
{
	D3D11_MAPPED_SUBRESOURCE MappedRes;

	EngineCore::GetContext()->Map(SpriteDataBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedRes);
	memcpy_s(MappedRes.pData, sizeof(SpriteData), CurSpriteData, sizeof(SpriteData));

	EngineCore::GetContext()->Unmap(SpriteDataBuffer, 0);
	EngineCore::GetContext()->PSSetConstantBuffers(1, 1, &SpriteDataBuffer);
}

