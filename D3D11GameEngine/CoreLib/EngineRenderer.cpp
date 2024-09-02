#include "Pre.h"
#include "EngineCore.h"
#include "EngineRenderer.h"
#include "EngineCamera.h"

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

	TransformBuffer = (IEngineConstantBuffer*)D3DManager->CreateResource(ResType::CB, BufferName);
	TransformBuffer->Setting(&Transform.WorldViewProjectionMat, sizeof(float4x4));

	Mesh = (IMesh*)D3DManager->Find(ResType::Mesh,"Box2D");
	Material = (IMaterial*)D3DManager->Find(ResType::Material, "Sprite2D");

	pIA = D3DManager->FindIA(Mesh, Material);
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

	Device->GetContext()->DrawIndexed(Mesh->GetIndexCount(), 0, 0);
}


void EngineRenderer::SetTexture(const char* _Name)
{
	Material->SetTexture(_Name);
	IEngineTexture* Texture = (IEngineTexture*)D3DManager->Find(ResType::Texture, _Name);
	float4 ImageScale = Texture->GetImageScale();
	Transform.SetLocalScale(ImageScale); 
}

void EngineRenderer::SetSampler(const char* _Name)
{
	Material->SetSampler(_Name);
	IEngineSampler* Sampler = (IEngineSampler*)D3DManager->Find(ResType::Sampler, _Name);
}
