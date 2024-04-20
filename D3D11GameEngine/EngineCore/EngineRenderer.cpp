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


	constantBuffer->Release();
	constantBuffer = nullptr;
}

void EngineRenderer::Start()
{
	GetLevel()->GetMainCamera()->PushRenderer(this);
	VB = EngineVertexBuffer::Find("Rect");
	IB = EngineIndexBuffer::Find("Rect");
	VS = EngineVertexShader::Find("TestShader");
	PS = EnginePixelShader::Find("TestShader");
	IA = EngineInputLayout::Find("POSITION");

	IA->CreateResource(VS->GetShaderByteCode(), VS->GetShaderByteLength());

	D3D11_BUFFER_DESC cbDesc;
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbDesc.ByteWidth = sizeof(float4x4);
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	HRESULT OK = EngineCore::GetDevice()->CreateBuffer(&cbDesc, nullptr, &constantBuffer);

}
void EngineRenderer::Render()
{
	UpdateConstantBuffer();
	VB->IntoPipeLine();
	IB->IntoPipeLine();
	IA->IntoPipeLine();
	VS->IntoPipeLine();
	PS->IntoPipeLine();
	EngineCore::GetContext()->DrawIndexed(6, 0, 0);
}

void EngineRenderer::UpdateConstantBuffer()
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	EngineCore::GetContext()->Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	void* dataPtr = mappedResource.pData;
	memcpy_s(dataPtr, sizeof(float4x4), &Transform.WorldViewProjectionMat, sizeof(float4x4));

	EngineCore::GetContext()->Unmap(constantBuffer, 0);
	EngineCore::GetContext()->VSSetConstantBuffers(0, 1, &constantBuffer);
}

