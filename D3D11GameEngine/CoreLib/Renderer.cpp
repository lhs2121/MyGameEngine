#include "Pre.h"
#include "Engine.h"
#include "Renderer.h"
#include "Camera.h"

Renderer::~Renderer()
{
}

void Renderer::Awake()
{
	pCamera = scene->GetMainCamera();
	pCamera->AddRenderer(this);

	static int RendererTransformBufferCount = 0;
	EngineString BufferName = "Transform_";
	BufferName += RendererTransformBufferCount;
	RendererTransformBufferCount++;

	pTransformBuffer = (IConstantBuffer*)mainResManager->CreateResource(ResType::CB, BufferName);
	pTransformBuffer->Setting(&transform.worldViewProjectionMat, sizeof(float4x4));

	pMesh = (IMesh*)mainResManager->Find(ResType::Mesh, "Box2D");
	pMaterial = (IMaterial*)mainResManager->Find(ResType::Material, "Sprite2D");

	pIA = mainResManager->GenerateInputLayout(pMesh, pMaterial);
}

void Renderer::Update(float _deltaTime)
{
}
void Renderer::Render()
{
	pTransformBuffer->IntoPipeline(ShaderType::VS);
	pIA->IntoPipeline();
	pMesh->IntoPipeline();
	pMaterial->IntoPipeline();

	mainDevice->GetContext()->DrawIndexed(pMesh->GetIndexCount(), 0, 0);
}

void Renderer::SetMesh(const char* _name)
{
	pMesh = (IMesh*)mainResManager->Find(ResType::Mesh, _name);
	pIA = mainResManager->GenerateInputLayout(pMesh, pMaterial);
}

void Renderer::SetMaterial(const char* _name)
{
	pMaterial = (IMaterial*)mainResManager->Find(ResType::Material, _name);
	pIA = mainResManager->GenerateInputLayout(pMesh, pMaterial);
}

void Renderer::SetTexture(const char* _name)
{
	ITexture* Texture = (ITexture*)mainResManager->Find(ResType::Texture, _name);
	pMaterial->SetTexture(_name);
}

void Renderer::SetRenderOrder(int _order)
{
	pCamera->ChangeRenderOrder(this, _order);
	renderOrder = _order;
}

