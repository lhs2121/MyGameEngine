#include "Pre.h"
#include "EngineInputLayout.h"


EngineInputLayout::EngineInputLayout()
{
	
}

EngineInputLayout::~EngineInputLayout()
{
}

void EngineInputLayout::Setting(D3D11_INPUT_ELEMENT_DESC* _Desc, UINT _ElementNum, void* ShaderBytecode, SIZE_T BytecodeLength)
{
	Desc = _Desc;
	HRESULT Result = DevicePtr->GetDevice()->CreateInputLayout(Desc, _ElementNum, ShaderBytecode, BytecodeLength, &LayoutPtr);
}

void EngineInputLayout::Release()
{
	if (LayoutPtr != nullptr)
	{
		LayoutPtr->Release();
		LayoutPtr = nullptr;
	}
}

void EngineInputLayout::IntoPipeLine()
{
	DevicePtr->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DevicePtr->GetContext()->IASetInputLayout(LayoutPtr);
}

