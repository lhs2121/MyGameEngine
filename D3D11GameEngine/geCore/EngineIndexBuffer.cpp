#include "Pre.h"
#include "EngineIndexBuffer.h"


EngineIndexBuffer::EngineIndexBuffer()
{
}

EngineIndexBuffer::~EngineIndexBuffer()
{
	if (BufferPtr != nullptr)
	{
		delete BufferPtr;
		BufferPtr = nullptr;
	}
}

void EngineIndexBuffer::SetResource(UINT* Indices, int IndexSize)
{
	D3D11_BUFFER_DESC Desc;
	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = Indices;
	Data.SysMemPitch = 0;
	Data.SysMemSlicePitch = 0;

	Desc.ByteWidth = IndexSize;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D10_BIND_INDEX_BUFFER;
	Desc.CPUAccessFlags = 0;
	Desc.StructureByteStride = 0;
	Desc.MiscFlags = 0;

	Strides = sizeof(UINT);
	Offsets = 0;
	HRESULT Result = EngineCore::GetDevice()->CreateBuffer(&Desc, &Data, &BufferPtr);
}

void EngineIndexBuffer::IntoPipeLine()
{
	EngineCore::GetContext()->IASetVertexBuffers(0, 1, &BufferPtr, &Strides, &Offsets);
}
