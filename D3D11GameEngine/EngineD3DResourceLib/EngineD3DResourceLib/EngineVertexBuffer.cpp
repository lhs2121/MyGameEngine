#include "Pre.h"
#include "EngineVertexBuffer.h"

EngineVertexBuffer::EngineVertexBuffer()
{
}

EngineVertexBuffer::~EngineVertexBuffer()
{
	if (BufferPtr != nullptr)
	{
		BufferPtr->Release();
		BufferPtr = nullptr;
	}
}

void EngineVertexBuffer::IntoPipeLine()
{
	m_pDevice->GetContext()->IASetVertexBuffers(0, 1, &BufferPtr, &Strides, &Offsets);
}

