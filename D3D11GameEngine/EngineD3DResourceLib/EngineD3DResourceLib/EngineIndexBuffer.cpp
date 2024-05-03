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

void EngineIndexBuffer::IntoPipeLine()
{
	Device->GetContext()->IASetIndexBuffer(BufferPtr, DXGI_FORMAT_R32_UINT, 0);
}

