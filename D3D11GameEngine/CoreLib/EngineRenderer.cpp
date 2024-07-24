#include "Pre.h"
#include "EngineCore.h"
#include "EngineRenderer.h"
#include "EngineCamera.h"
#include "Singleton.h"

EngineRenderer::~EngineRenderer()
{
	if (TransformBuffer != nullptr)
	{
		TransformBuffer->Release();
		TransformBuffer = nullptr;
	}
}

void EngineRenderer::Awake()
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

		TransformBuffer = MainD3DManager->CreateConstantBuffer("Transform");
		TransformBuffer->Setting(Desc, &Transform.WorldViewProjectionMat,sizeof(float4x4));
	}



	VB = MainD3DManager->FindVertexBuffer("Box2DTex");
	IB = MainD3DManager->FindIndexBuffer("Box2D");
	IA = MainD3DManager->FindInputLayout("PosTexcoord");
	VS = MainD3DManager->FindVertexShader("TestSpriteShader");
	PS = MainD3DManager->FindPixelShader("TestSpriteShader");
	RS = MainD3DManager->FindRasterizer("Default");
	DS = MainD3DManager->FindDepthStencil("Default");

	//SetTexture("Default");
	SetSampler("Default");
}

void EngineRenderer::Update(float _Delta)
{
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

	TransformBuffer->IntoPipeLine(ShaderType::VS);

	UINT IndexCount = IB->GetIndexCount();
	MainDevice->GetContext()->DrawIndexed(IndexCount, 0, 0);
}


void EngineRenderer::SetTexture(EngineString _Name)
{
	CurTexture = MainD3DManager->FindTexture(_Name);
	CurTexture->IntoPipeLine(ShaderType::PS);

	float4 ImageScale = CurTexture->GetImageScale();
	Transform.SetScale(ImageScale);
}

void EngineRenderer::SetSampler(EngineString _Name)
{
	IEngineSampler* Sampler = MainD3DManager->FindSampler(_Name);
	Sampler->IntoPipeLine(ShaderType::PS);
}
