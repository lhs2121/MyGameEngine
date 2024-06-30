#include "Pre.h"
#include "EngineRenderer.h"
#include "EngineCamera.h"

EngineRenderer::EngineRenderer()
{
}

EngineRenderer::~EngineRenderer()
{
	if (ConstantBuffer != nullptr)
	{
		ConstantBuffer->Release();
		ConstantBuffer = nullptr;
	}

	if (SpriteCBuffer != nullptr)
	{
		SpriteCBuffer->Release();
		SpriteCBuffer = nullptr;
	}

	if (SpriteIndex != nullptr)
	{
		delete SpriteIndex;
		SpriteIndex = nullptr;
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

		HRESULT OK = EngineCore::GetDevice()->CreateBuffer(&Desc, nullptr, &ConstantBuffer);
	}
	

	{
		D3D11_BUFFER_DESC Desc = { 0 };
		Desc.Usage = D3D11_USAGE_DYNAMIC;
		Desc.ByteWidth = sizeof(SpriteData);
		Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		Desc.MiscFlags = 0;
		Desc.StructureByteStride = 0;

		HRESULT OK = EngineCore::GetDevice()->CreateBuffer(&Desc, nullptr, &SpriteCBuffer);
	}

	IEngineD3DManager* ResManager = EngineCore::GetMainD3DManager();
	VB = ResManager->FindVertexBuffer("Box2DTex");
	IB = ResManager->FindIndexBuffer("Box2D");
	IA = ResManager->FindInputLayout("PosTexcoord");
	VS = ResManager->FindVertexShader("TestSpriteShader");
	PS = ResManager->FindPixelShader("TestSpriteShader");
	RS = ResManager->FindRasterizer("Default");
	DS = ResManager->FindDepthStencil("Default");

	SetSampler("Default");
}
void EngineRenderer::Update(float _Delta)
{
	UpdateConstantBuffer();
	
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
	
	EngineCore::GetContext() ->DrawIndexed(IB->GetIndexCount(), 0, 0);
}

void EngineRenderer::SetTexture(EngineString _Name)
{
	Texture = EngineCore::GetMainD3DManager()->FindTexture(_Name);
	ID3D11ShaderResourceView* SRV = Texture->GetSRV();
	float4 ImageScale = Texture->GetImageScale();
	Transform.SetScale(ImageScale);
	EngineCore::GetContext()->PSSetShaderResources(0, 1, &SRV);
}

void EngineRenderer::SetSampler(EngineString _Name)
{
	IEngineSampler* Sam = EngineCore::GetMainD3DManager()->FindSampler(_Name);
	ID3D11SamplerState* State = Sam->GetState();
	EngineCore::GetContext()->PSSetSamplers(0, 1, &State);
}

void EngineRenderer::CreateAnimation(int TileCountX, int TileCountY)
{
	if (Texture == nullptr)
	{
		EngineDebug::MsgBoxAssert("애니메이션을 만들기 전에 텍스처를 설정하세요");
	}
	SpriteIndex = new std::vector<std::vector<SpriteData>>(TileCountY, std::vector<SpriteData>(TileCountX));

	float2 Ratio = {1 / static_cast<float>(TileCountX), 1 / static_cast<float>(TileCountY)};

	for (int y = 0; y < TileCountY; y++)
	{
		for (int x = 0; x < TileCountX; x++)
		{
			SpriteData& a = (*SpriteIndex)[y][x];
			a.ResizeRatio = Ratio;
			a.Offset.x = Ratio.x * x;
			a.Offset.y = Ratio.y * y;
		}
	}
	
}

void EngineRenderer::SetAnimation()
{

}

void EngineRenderer::UpdateConstantBuffer()
{
	{
		D3D11_MAPPED_SUBRESOURCE MappedResource;

		EngineCore::GetContext()->Map(ConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);
		memcpy_s(MappedResource.pData, sizeof(float4x4), &Transform.WorldViewProjectionMat, sizeof(float4x4));

		EngineCore::GetContext()->Unmap(ConstantBuffer, 0);
		EngineCore::GetContext()->VSSetConstantBuffers(0, 1, &ConstantBuffer);
	}

	{
		static int i = 0;
		static int j = 0;
		

		if (i == 4)
		{
			i = 0;
			j++;
			if (j == 4)
			{
				j = 0;
			}
		}

		SpriteData& a = (*SpriteIndex)[j][i];
		D3D11_MAPPED_SUBRESOURCE MappedResource;

		i++;

		EngineCore::GetContext()->Map(SpriteCBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);
		memcpy_s(MappedResource.pData, sizeof(SpriteData), &a, sizeof(SpriteData));

		EngineCore::GetContext()->Unmap(SpriteCBuffer, 0);
		EngineCore::GetContext()->PSSetConstantBuffers(1, 1, &SpriteCBuffer);
	}
}

