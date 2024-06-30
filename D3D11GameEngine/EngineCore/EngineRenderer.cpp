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

}
void EngineRenderer::Render()
{
	UpdateConstantBuffer();
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

void EngineRenderer::CreateAnimation(int SliceX, int SliceY)
{
	if (Texture != nullptr)
	{
		EngineDebug::MsgBoxAssert("애니메이션을 만들기 전에 텍스처를 설정하세요");
	}
	float4 ImageScale = Texture->GetImageScale();
	
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
		static 	SpriteData Data;
		Data.ResizeRatio = { 1,1 };

		if (KeyIsPress('B'))
		{
			Data.ResizeRatio.x += 0.01f;
			Data.ResizeRatio.y += 0.01f;
		}

		if (KeyIsPress('N'))
		{
			Data.ResizeRatio.x -= 0.01f;
			Data.ResizeRatio.y -= 0.01f;
		}
		D3D11_MAPPED_SUBRESOURCE MappedResource;

		EngineCore::GetContext()->Map(SpriteCBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);
		memcpy_s(MappedResource.pData, sizeof(SpriteData), &Data, sizeof(SpriteData));

		EngineCore::GetContext()->Unmap(SpriteCBuffer, 0);
		EngineCore::GetContext()->PSSetConstantBuffers(1, 1, &SpriteCBuffer);
	}
}

