#include "Pre.h"
#include "EngineCore.h"
#include "EngineRenderer.h"
#include "EngineCamera.h"
#include "Singleton.h"

EngineRenderer::~EngineRenderer()
{
}

void EngineRenderer::Awake()
{
	GetLevel()->GetMainCamera()->PushRenderer(this);

	static int RendererTransformBufferCount = 0;
	EngineString BufferName = "Transform_";
	BufferName += RendererTransformBufferCount;
	RendererTransformBufferCount++;

	TransformBuffer = (IEngineConstantBuffer*)MainD3DManager->CreateResource(ResType::CB, BufferName);
	TransformBuffer->Setting(&Transform.WorldViewProjectionMat, sizeof(float4x4));

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
	pIA->IntoPipeline();
	Mesh->IntoPipeline();
	Material->IntoPipeline();

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
