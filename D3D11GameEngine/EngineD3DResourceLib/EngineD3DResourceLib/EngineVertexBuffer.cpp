#include "Pre.h"
#include "EngineVertexBuffer.h"

EngineVertexBuffer::EngineVertexBuffer()
{
}

EngineVertexBuffer::~EngineVertexBuffer()
{
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
	DeviceContext->IASetVertexBuffers(0, 1, &BufferPtr, &Strides, &Offsets);
}

