#include "Pre.h"
#include "EngineInputLayout.h"


EngineInputLayout::EngineInputLayout()
{
}

EngineInputLayout::~EngineInputLayout()
{
	LayoutPtr->Release();
}

D3D11_INPUT_ELEMENT_DESC* EngineInputLayout::GetLayoutDesc()
{
	return DescPtr;
}

void EngineInputLayout::CreateResourceWithDevice(D3D11_INPUT_ELEMENT_DESC* Layouts, UINT LayoutNum, void* ShaderBytecode, SIZE_T BytecodeLength)
{
	DescPtr = Layouts;
	EngineCore::GetDevice()->CreateInputLayout(Layouts, LayoutNum, ShaderBytecode, BytecodeLength, &LayoutPtr);
}

void EngineInputLayout::IntoPipeLine()
{
	EngineCore::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	EngineCore::GetContext()->IASetInputLayout(LayoutPtr);
}

