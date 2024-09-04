#include "Pre.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
}

VertexBuffer::~VertexBuffer()
{
	if (BufferPtr != nullptr)
	{
		BufferPtr->Release();
		BufferPtr = nullptr;
	}
}

void VertexBuffer::Setting(ID3D11Device* DevicePtr, void* pVertices, int VertexFormatSize, int VertexSize, UINT _SlotNumber)
{
	D3D11_BUFFER_DESC Desc;
	D3D11_SUBRESOURCE_DATA Data;

	Data.pSysMem = pVertices;
	Data.SysMemPitch = 0;
	Data.SysMemSlicePitch = 0;

	Desc.ByteWidth = VertexSize;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	Desc.CPUAccessFlags = 0;
	Desc.StructureByteStride = 0;
	Desc.MiscFlags = 0;

	Strides = VertexFormatSize;
	Offsets = 0;
	SlotNumber = _SlotNumber;
	HRESULT Result = DevicePtr->CreateBuffer(&Desc, &Data, &BufferPtr);
}

void VertexBuffer::IntoPipeline(ID3D11DeviceContext* ContextPtr)
{
	ContextPtr->IASetVertexBuffers(SlotNumber, 1, &BufferPtr, &Strides, &Offsets);
}

