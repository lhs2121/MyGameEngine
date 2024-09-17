#include "Pre.h"
#include "Engine.h"
#include "Renderer.h"
#include "Camera.h"

Renderer::~Renderer()
{
	if (pMaterial != nullptr)
	{
		delete pMaterial;
	}
}

void Renderer::Awake()
{
	pContext = Device::GetContext();

	pCamera = GetScene()->GetMainCamera();
	pCamera->AddRenderer(this);

	Naming::AddName("Transform");

	base::string name = Naming::GetName("Transform");
	pTransformBuffer = Resource::CreateConstantBuffer(name.c_str(), &transform.worldViewProjectionMat, sizeof(float4x4), ShaderType::VS);

	pMesh = Resource::FindMesh("Box2D");
	pMaterial = new Material();
	Material* findMaterial = Resource::FindMaterial("Sprite2D");
	memcpy_s(pMaterial, sizeof(Material), findMaterial, sizeof(Material));
	pMaterial->name = nullptr;
	pMaterial->name = findMaterial->name;

	pIA = Resource::FindInputLayout("POSITION_TEXCOORD");
	if (pIA == nullptr)
	{
		pIA = Resource::CreateInputLayout("POSITION_TEXCOORD", pMaterial->pVertexShader);
	}

}

void Renderer::Update(float _deltaTime)
{
}

void Renderer::Release()
{
	pCamera->DeleteRenderer(this);
}

void Renderer::Render()
{
	pTransformBuffer->Draw();
	pMesh->Draw();
	pMaterial->Draw();
	pIA->Draw();
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pContext->DrawIndexed(pMesh->pIndexBuffer->count, 0, 0);
}

void Renderer::SetMesh(const char* _name)
{
	pMesh = Resource::FindMesh(_name);
}

void Renderer::SetMaterial(const char* _name)
{
	Material* findMaterial = Resource::FindMaterial(_name);
	memcpy_s(pMaterial, sizeof(Material), findMaterial, sizeof(Material));
	pMaterial->name = nullptr;
	pMaterial->name = findMaterial->name;
}

void Renderer::SetRenderOrder(int _order)
{
	pCamera->ChangeRenderOrder(this, _order);
	renderOrder = _order;
}

