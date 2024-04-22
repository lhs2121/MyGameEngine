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
	EngineCore::GetDevice()->CreateInputLayout(LayoutDesc, ElementNum, ShaderBytecode, BytecodeLength, &LayoutPtr);
}

void EngineInputLayout::SetDesc(UINT _ElementNum,D3D11_INPUT_ELEMENT_DESC* _Desc)
{
	ElementNum = _ElementNum;
	LayoutDesc = _Desc;
}

void EngineInputLayout::IntoPipeLine()
{
	EngineCore::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	EngineCore::GetContext()->IASetInputLayout(LayoutPtr);
}

