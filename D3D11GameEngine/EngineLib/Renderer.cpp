#include "Pre.h"
#include "Engine.h"
#include "Renderer.h"
#include "Camera.h"

Renderer::~Renderer()
{
	if (pMesh != nullptr)
	{
		delete pMesh;
	}
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

	pMaterial = Resource::FindMaterial("Sprite2D");

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
	if (pMesh != nullptr)
		delete pMesh;
	
	pMesh = Resource::FindMesh(_name);
}

void Renderer::SetMaterial(const char* _name)
{
	if(pMaterial != nullptr)
		delete pMaterial;

	pMaterial = Resource::FindMaterial(_name);
}

void Renderer::SetRenderOrder(int _order)
{
	pCamera->ChangeRenderOrder(this, _order);
	renderOrder = _order;
}

