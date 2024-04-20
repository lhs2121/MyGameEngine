#include "Pre.h"
#include "EngineInputLayout.h"


EngineInputLayout::EngineInputLayout()
{
}

EngineInputLayout::~EngineInputLayout()
{
	if (LayoutPtr != nullptr)
	{
		LayoutPtr->Release();
		LayoutPtr = nullptr;
	}
}

void EngineInputLayout::CreateResource(void* ShaderBytecode, SIZE_T BytecodeLength)
{
	EngineCore::GetDevice()->CreateInputLayout(&LayoutDesc, 1, ShaderBytecode, BytecodeLength, &LayoutPtr);
}

void EngineInputLayout::SetDesc(D3D11_INPUT_ELEMENT_DESC _Desc)
{
	LayoutDesc = _Desc;
}

void EngineInputLayout::IntoPipeLine()
{
	EngineCore::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	EngineCore::GetContext()->IASetInputLayout(LayoutPtr);
}

