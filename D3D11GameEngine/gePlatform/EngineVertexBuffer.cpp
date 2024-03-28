#include "Pre.h"
#include "EngineVertexBuffer.h"


EngineVertexBuffer::EngineVertexBuffer()
{
}

EngineVertexBuffer::~EngineVertexBuffer()
{
}

void EngineVertexBuffer::SetResource(float4* Vertices, int VertexSize)
{
	D3D11_BUFFER_DESC Desc;
	D3D11_SUBRESOURCE_DATA Data;
	ID3D11Buffer* VB;

	Data.pSysMem = Vertices;
	Data.SysMemPitch = 0;
	Data.SysMemSlicePitch = 0;

	Desc.ByteWidth = VertexSize;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	Desc.CPUAccessFlags = 0;
	Desc.StructureByteStride = 0;
	Desc.MiscFlags = 0;

	Strides = sizeof(float4);
	Offsets = 0;
	HRESULT Result = EngineCore::GetDevice()->CreateBuffer(&Desc, &Data, &VB);
}

void EngineVertexBuffer::IntoPipeLine()
{
	EngineCore::GetContext()->IASetVertexBuffers(0, 1, &VertexBufferPtr, &Strides, &Offsets);
}
