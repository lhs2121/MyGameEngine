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

void VertexBuffer::Setting(void* pVertices, int _Stride, int _ByteWidth, UINT _SlotNumber)
{
	D3D11_BUFFER_DESC Desc;
	D3D11_SUBRESOURCE_DATA Data;

	Data.pSysMem = pVertices;
	Data.SysMemPitch = 0;
	Data.SysMemSlicePitch = 0;

	Desc.ByteWidth = _ByteWidth;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	Desc.CPUAccessFlags = 0;
	Desc.StructureByteStride = 0;
	Desc.MiscFlags = 0;

	Strides = _Stride;
	Offsets = 0;
	SlotNumber = _SlotNumber;
	HRESULT Result = DevicePtr->CreateBuffer(&Desc, &Data, &BufferPtr);
}

void VertexBuffer::IntoPipeline()
{
	ContextPtr->IASetVertexBuffers(SlotNumber, 1, &BufferPtr, &Strides, &Offsets);
}

