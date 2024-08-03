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

	Mesh = (IMesh*)MainD3DManager->Find(ResType::Mesh,"Box2D");
	Material = (IMaterial*)MainD3DManager->Find(ResType::Material, "Default");

	pIA = MainD3DManager->FindIA(Mesh, Material);

	SetTexture("Default");
	SetSampler("Default");
}

void EngineRenderer::Update(float _Delta)
{
}
void EngineRenderer::Render()
{
	TransformBuffer->IntoPipeline(ShaderType::VS);
	Mesh->IntoPipeline();
	Material->IntoPipeline();
	pIA->IntoPipeline();
	MainDevice->GetContext()->DrawIndexed(Mesh->GetIndexCount(), 0, 0);
}


void EngineRenderer::SetTexture(const char* _Name)
{
	Material->SetTexture(_Name);

	IEngineTexture* Texture = (IEngineTexture*)MainD3DManager->Find(ResType::Texture, _Name);
	float4 ImageScale = Texture->GetImageScale();
	Transform.SetScale(ImageScale);
}

void EngineRenderer::SetSampler(const char* _Name)
{
	Material->SetSampler(_Name);
	IEngineSampler* Sampler = (IEngineSampler*)MainD3DManager->Find(ResType::Sampler, _Name);
}
