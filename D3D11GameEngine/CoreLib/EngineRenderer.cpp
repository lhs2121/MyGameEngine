#include "Pre.h"
#include "EngineCore.h"
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

	IEngineD3DManager* Manager = EngineCore::GetMainD3DManager();
	
	{
		D3D11_BUFFER_DESC Desc = { 0 };
		Desc.Usage = D3D11_USAGE_DYNAMIC;
		Desc.ByteWidth = sizeof(float4x4);
		Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		Desc.MiscFlags = 0;
		Desc.StructureByteStride = 0;

		TransformBuffer = Manager->CreateConstantBuffer("Transform");
		TransformBuffer->Setting(Desc, &Transform.WorldViewProjectionMat,sizeof(float4x4));
	}



	VB = Manager->FindVertexBuffer("Box2DTex");
	IB = Manager->FindIndexBuffer("Box2D");
	IA = Manager->FindInputLayout("PosTexcoord");
	VS = Manager->FindVertexShader("TestSpriteShader");
	PS = Manager->FindPixelShader("TestSpriteShader");
	RS = Manager->FindRasterizer("Default");
	DS = Manager->FindDepthStencil("Default");

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
	EngineCore::GetContext()->DrawIndexed(IndexCount, 0, 0);
}


void EngineRenderer::SetTexture(EngineString _Name)
{
	CurTexture = EngineCore::GetMainD3DManager()->FindTexture(_Name);
	CurTexture->IntoPipeLine(ShaderType::PS);

	float4 ImageScale = CurTexture->GetImageScale();
	Transform.SetScale(ImageScale);
}

void EngineRenderer::SetSampler(EngineString _Name)
{
	IEngineSampler* Sampler = EngineCore::GetMainD3DManager()->FindSampler(_Name);
	Sampler->IntoPipeLine(ShaderType::PS);
}
