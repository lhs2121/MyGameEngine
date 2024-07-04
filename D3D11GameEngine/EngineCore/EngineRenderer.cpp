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

	IEngineD3DManager* Manager = EngineCore::GetMainD3DManager();

	VB = Manager->FindVertexBuffer("Box2DTex");
	IB = Manager->FindIndexBuffer("Box2D");
	IA = Manager->FindInputLayout("PosTexcoord");
	VS = Manager->FindVertexShader("TestSpriteShader");
	PS = Manager->FindPixelShader("TestSpriteShader");
	RS = Manager->FindRasterizer("Default");
	DS = Manager->FindDepthStencil("Default");

	BindTexture("Default");
	BindSampler("Default");
}

void EngineRenderer::Update(float _Delta)
{
}
void EngineRenderer::Render()
{
	BindTransform();

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


void EngineRenderer::BindTexture(EngineString _Name)
{
	CurTexture = EngineCore::GetMainD3DManager()->FindTexture(_Name);
	CurTexture->IntoPipeLine();

	float4 ImageScale = CurTexture->GetImageScale();
	Transform.SetScale(ImageScale);
}

void EngineRenderer::BindSampler(EngineString _Name)
{
	IEngineSampler* Sampler = EngineCore::GetMainD3DManager()->FindSampler(_Name);
	Sampler->IntoPipeLine();
}

void EngineRenderer::BindTransform() 
{
	D3D11_MAPPED_SUBRESOURCE MappedRes;

	EngineCore::GetContext()->Map(TransformBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedRes);
	memcpy_s(MappedRes.pData, sizeof(float4x4), &Transform.WorldViewProjectionMat, sizeof(float4x4));

	EngineCore::GetContext()->Unmap(TransformBuffer, 0);
	EngineCore::GetContext()->VSSetConstantBuffers(0, 1, &TransformBuffer);
}