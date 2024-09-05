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

	TransformBuffer = (IConstantBuffer*)ResManager->CreateResource(ResType::CB, BufferName);
	TransformBuffer->Setting(&Transform.WorldViewProjectionMat, sizeof(float4x4));

	Mesh = (IMesh*)ResManager->Find(ResType::Mesh, "Box2D");
	Material = (IMaterial*)ResManager->Find(ResType::Material, "Sprite2D");

	pIA = ResManager->GenerateInputLayout(Mesh, Material);
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

void EngineRenderer::SetMesh(const char* _Name)
{
	Mesh = (IMesh*)ResManager->Find(ResType::Mesh, _Name);
	pIA = ResManager->GenerateInputLayout(Mesh, Material);
}

void EngineRenderer::SetMaterial(const char* _Name)
{
	Material = (IMaterial*)ResManager->Find(ResType::Material, _Name);
	pIA = ResManager->GenerateInputLayout(Mesh, Material);
}

void EngineRenderer::SetTexture(const char* _TextureName)
{
	ITexture* Texture = (ITexture*)ResManager->Find(ResType::Texture, _TextureName);
	Transform.SetLocalScale(Texture->GetImageScale());
	Material->SetTexture(_TextureName);
}

