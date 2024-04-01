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

void EngineRenderer::Start()
{
	VB = EngineVertexBuffer::Find("Rect");
	IB = EngineIndexBuffer::Find("Rect");
	IA = EngineInputLayout::Find("Pos");
	VS = EngineVertexShader::Find("TestShader");
	PS = EnginePixelShader::Find("TestShader");
}
void EngineRenderer::Render()
{
	VB->IntoPipeLine();
	IB->IntoPipeLine();
	IA->IntoPipeLine();
	VS->IntoPipeLine();
	PS->IntoPipeLine();

	EngineCore::GetContext()->DrawIndexed(6,0,0);
}

