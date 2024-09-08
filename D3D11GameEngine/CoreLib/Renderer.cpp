#include "Pre.h"
#include "Engine.h"
#include "Renderer.h"
#include "Camera.h"

Renderer::~Renderer()
{
}

void Renderer::Awake()
{
	Name = "Renderer";
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

void Renderer::Update(float _Delta)
{
}
void Renderer::Render()
{
	TransformBuffer->IntoPipeline(ShaderType::VS);
	pIA->IntoPipeline();
	Mesh->IntoPipeline();
	Material->IntoPipeline();

	Device->GetContext()->DrawIndexed(Mesh->GetIndexCount(), 0, 0);
}

void Renderer::SetMesh(const char* _Name)
{
	Mesh = (IMesh*)ResManager->Find(ResType::Mesh, _Name);
	pIA = ResManager->GenerateInputLayout(Mesh, Material);
}

void Renderer::SetMaterial(const char* _Name)
{
	Material = (IMaterial*)ResManager->Find(ResType::Material, _Name);
	pIA = ResManager->GenerateInputLayout(Mesh, Material);
}

void Renderer::SetTexture(const char* _TextureName)
{
	ITexture* Texture = (ITexture*)ResManager->Find(ResType::Texture, _TextureName);
	ImageScale = Texture->GetImageScale();
	Transform.SetLocalScale(ImageScale);
	Material->SetTexture(_TextureName);
}

