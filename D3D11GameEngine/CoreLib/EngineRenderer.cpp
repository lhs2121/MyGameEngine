#include "Pre.h"
#include "EngineCore.h"
#include "EngineRenderer.h"
#include "EngineCamera.h"
#include "Singleton.h"

EngineRenderer::~EngineRenderer()
{
	if (TransformBuffer != nullptr)
	{
		delete TransformBuffer;
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

		TransformBuffer = (IEngineConstantBuffer*)MainD3DManager->CreateResource(ResType::CB, "Transform");
		TransformBuffer->Setting(Desc, &Transform.WorldViewProjectionMat, sizeof(float4x4));
	}



	VB = (IEngineVertexBuffer*)MainD3DManager->Find(ResType::VB, "Box2DTex");
	IB = (IEngineIndexBuffer*)MainD3DManager->Find(ResType::IB, "Box2D");
	IA = (IEngineInputLayout*)MainD3DManager->Find(ResType::IA, "PosTexcoord");
	VS = (IEngineVertexShader*)MainD3DManager->Find(ResType::VS, "TestSpriteShader");
	PS = (IEnginePixelShader*)MainD3DManager->Find(ResType::PS, "TestSpriteShader");
	RS = (IEngineRasterizer*)MainD3DManager->Find(ResType::RS, "Default");
	DS = (IEngineDepthStencil*)MainD3DManager->Find(ResType::DS, "Default");

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


void EngineRenderer::SetTexture(const char* _Name)
{
	CurTexture = (IEngineTexture*)MainD3DManager->Find(ResType::Texture, _Name);
	CurTexture->IntoPipeLine(ShaderType::PS);

	float4 ImageScale = CurTexture->GetImageScale();
	Transform.SetScale(ImageScale);
}

void EngineRenderer::SetSampler(const char* _Name)
{
	IEngineSampler* Sampler = (IEngineSampler*)MainD3DManager->Find(ResType::Sampler, _Name);
	Sampler->IntoPipeLine(ShaderType::PS);
}
