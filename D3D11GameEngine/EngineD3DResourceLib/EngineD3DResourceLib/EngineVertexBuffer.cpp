#include "Pre.h"
#include "EngineVertexBuffer.h"
#include "EngineVertexFormat.h"

static std::map<const char*, EngineVertexBuffer*> Resources;

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

