#include "Pre.h"
#include "EngineInputLayout.h"
#include "EngineVertexShader.h"

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

void EngineInputLayout::Setting(D3D11_INPUT_ELEMENT_DESC* _Desc, UINT _ElementNum, IEngineVertexShader* _VSPtr)
{
	Desc = _Desc;
	EngineVertexShader* VSPtr = (EngineVertexShader*)_VSPtr;
	HRESULT Result = DevicePtr->CreateInputLayout(Desc, _ElementNum, VSPtr->GetShaderByteCode(), VSPtr->GetShaderByteLength(), &LayoutPtr);
}

void EngineInputLayout::IntoPipeLine()
{
	ContextPtr->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	ContextPtr->IASetInputLayout(LayoutPtr);
}

