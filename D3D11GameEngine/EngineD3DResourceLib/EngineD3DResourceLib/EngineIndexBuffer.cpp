#include "Pre.h"
#include "EngineDevice.h"
#include "EngineIndexBuffer.h"


EngineIndexBuffer::EngineIndexBuffer()
{
}

EngineIndexBuffer::~EngineIndexBuffer()
{
}

void EngineIndexBuffer::Release()
{
	if (BufferPtr != nullptr)
	{
		BufferPtr->Release();
		BufferPtr = nullptr;
	}
}

void EngineIndexBuffer::IntoPipeLine()
{
	DeviceContext->IASetIndexBuffer(BufferPtr, DXGI_FORMAT_R32_UINT, 0);
}

