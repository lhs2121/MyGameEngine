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
	SetConstantBuffer(name.c_str(), &transform.matWorldViewProjection, sizeof(float4x4), ShaderType::VS);

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
	for (ConstantBuffer* cb : ConstantBuffers)
	{
		cb->Draw();
	}

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
	if (pMaterial != nullptr)
		delete pMaterial;

	pMaterial = Resource::FindMaterial(_name);
}

void Renderer::SetRenderOrder(int _order)
{
	pCamera->ChangeRenderOrder(this, _order);
	renderOrder = _order;
}

void Renderer::SetConstantBuffer(const char* _name, void* pData, int _dataSize, ShaderType _type, int _slot)
{
	ConstantBuffer* newCB = Resource::CreateConstantBuffer(_name, pData, _dataSize, _type, _slot);
	ConstantBuffers.push_back(newCB);
}

