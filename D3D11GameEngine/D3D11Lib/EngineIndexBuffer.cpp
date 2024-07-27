#include "Pre.h"
#include "EngineDevice.h"
#include "EngineIndexBuffer.h"


EngineIndexBuffer::EngineIndexBuffer()
{
}

EngineIndexBuffer::~EngineIndexBuffer()
{
	if (BufferPtr != nullptr)
	{
		BufferPtr->Release();
		BufferPtr = nullptr;
	}
}

void EngineIndexBuffer::Setting(UINT* Indices, int IndexSize)
{
	D3D11_BUFFER_DESC Desc;
	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = Indices;
	Data.SysMemPitch = 0;
	Data.SysMemSlicePitch = 0;

	Desc.ByteWidth = IndexSize;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	Desc.CPUAccessFlags = 0;
	Desc.StructureByteStride = 0;
	Desc.MiscFlags = 0;

	Strides = sizeof(UINT);
	Offsets = 0;

	IndexCount = IndexSize / sizeof(UINT);
	HRESULT Result = DevicePtr->CreateBuffer(&Desc, &Data, &BufferPtr);
}

void EngineIndexBuffer::IntoPipeLine()
{
	ContextPtr->IASetIndexBuffer(BufferPtr, DXGI_FORMAT_R32_UINT, 0);
}

