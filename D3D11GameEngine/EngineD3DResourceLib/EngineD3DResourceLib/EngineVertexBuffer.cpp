#include "Pre.h"
#include "EngineVertexBuffer.h"

EngineVertexBuffer::EngineVertexBuffer()
{
}

EngineVertexBuffer::~EngineVertexBuffer()
{
}

void EngineVertexBuffer::Setting(void* pVertices, int VertexFormatSize, int VertexSize)
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

	HRESULT Result = DevicePtr->GetDevice()->CreateBuffer(&Desc, &Data, &BufferPtr);
}

void EngineVertexBuffer::Release()
{
	if (BufferPtr != nullptr)
	{
		BufferPtr->Release();
		BufferPtr = nullptr;
	}
}

void EngineVertexBuffer::IntoPipeLine()
{
	DevicePtr->GetContext()->IASetVertexBuffers(0, 1, &BufferPtr, &Strides, &Offsets);
}

