#include "Pre.h"
#include "EngineRenderer.h"
#include "EngineCamera.h"

EngineRenderer::EngineRenderer()
{
}

EngineRenderer::~EngineRenderer()
{
}

void EngineRenderer::Start()
{
	GetLevel()->GetMainCamera()->PushRenderer(this);
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

