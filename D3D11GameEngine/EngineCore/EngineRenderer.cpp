#include "Pre.h"
#include "EngineRenderer.h"
#include "EngineCamera.h"

EngineRenderer::EngineRenderer()
{
}

EngineRenderer::~EngineRenderer()
{
	VB = nullptr;
	IB = nullptr;
	IA = nullptr;
	VS = nullptr;
	PS = nullptr;
	RS = nullptr;

	if (ConstantBuffer != nullptr)
	{
		ConstantBuffer->Release();
		ConstantBuffer = nullptr;
	}
}

void EngineRenderer::Start()
{
	GetLevel()->GetMainCamera()->PushRenderer(this);

	D3D11_BUFFER_DESC Desc = { 0 };
	Desc.Usage = D3D11_USAGE_DYNAMIC;
	Desc.ByteWidth = sizeof(float4x4);
	Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	Desc.MiscFlags = 0;
	Desc.StructureByteStride = 0;

	HRESULT OK = EngineCore::GetDevice()->CreateBuffer(&Desc, nullptr, &ConstantBuffer);

	IEngineD3DResourceManager* ResManager = EngineCore::GetMainResourceManager();
	VB = ResManager->FindVertexBuffer("Box2D");
	IB = ResManager->FindIndexBuffer("Box2D");
	IA = ResManager->FindInputLayout("Pos");
	VS = ResManager->FindVertexShader("Test2DShader");
	PS = ResManager->FindPixelShader("Test2DShader");
	RS = ResManager->FindRasterizer("Default");
	DS = ResManager->FindDepthStencil("Default");
}
void EngineRenderer::Render()
{
	UpdateConstantBuffer();
	VB->IntoPipeLine();
	IB->IntoPipeLine();
	IA->IntoPipeLine();
	VS->IntoPipeLine();
	RS->IntoPipeLine();
	PS->IntoPipeLine();
	DS->IntoPipeLine();
	
	EngineCore::GetContext() ->DrawIndexed(IB->GetIndexCount(), 0, 0);
}

void EngineRenderer::UpdateConstantBuffer()
{
	D3D11_MAPPED_SUBRESOURCE MappedResource;

	EngineCore::GetContext()->Map(ConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);

	void* DataPtr = MappedResource.pData;
	memcpy_s(DataPtr, sizeof(float4x4), &Transform.WorldViewProjectionMat, sizeof(float4x4));

	EngineCore::GetContext()->Unmap(ConstantBuffer, 0);
	EngineCore::GetContext()->VSSetConstantBuffers(0, 1, &ConstantBuffer);
}

