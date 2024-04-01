#include "Pre.h"
#include "EngineInputLayout.h"


EngineInputLayout::EngineInputLayout()
{
}

EngineInputLayout::~EngineInputLayout()
{
	if (LayoutPtr != nullptr)
	{
		delete LayoutPtr;
		LayoutPtr = nullptr;
	}
}

void EngineInputLayout::SetResource()
{
	//D3D11_INPUT_ELEMENT_DESC Layout[] =
	//{
	//	{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//};
	//SIZE_T BytecodeLength;
	//void* ShaderBytecode;

	//EngineCore::GetDevice()->CreateInputLayout(Layout, 2, ShaderBytecode, BytecodeLength, &LayoutPtr);
}

void EngineInputLayout::IntoPipeLine()
{
	EngineCore::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//EngineCore::GetContext()->IASetInputLayout();
}
