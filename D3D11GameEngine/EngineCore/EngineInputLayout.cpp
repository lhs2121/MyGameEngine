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

void EngineInputLayout::SetResource(D3D11_INPUT_ELEMENT_DESC* Layouts, UINT LayoutNum, void* ShaderBytecode, SIZE_T BytecodeLength)
{
	EngineCore::GetDevice()->CreateInputLayout(Layouts, LayoutNum, ShaderBytecode, BytecodeLength, &LayoutPtr);
}

void EngineInputLayout::IntoPipeLine()
{
	EngineCore::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	EngineCore::GetContext()->IASetInputLayout(LayoutPtr);
}
