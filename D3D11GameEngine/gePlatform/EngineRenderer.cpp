#include "Pre.h"
#include "EngineCore.h"
#include "EngineRenderer.h"
#include "EngineDevice.h"

EngineRenderer::EngineRenderer()
{
}

EngineRenderer::~EngineRenderer()
{
}

void EngineRenderer::Render()
{
	EngineCore::MainDevice.GetContext()->IASetVertexBuffers(VB->StartSlot, VB->NumBuffers, &VB->VertexBufferPtr, &VB->Strides, &VB->Offsets);
}

void EngineRenderer::SetVertexBuffer()
{
	VB = EngineCore::MainDevice.GetResource<EngineVertexBuffer>("Rect");
}
