#include "Pre.h"
#include "EngineInputLayout.h"
#include "EngineVertexShader.h"
#include "EngineVertexBuffer.h"

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

	if (Desc != nullptr) 
	{
		delete Desc;
		Desc = nullptr;
	}
}

void EngineInputLayout::Setting(IEngineVertexBuffer* _pVB, IEngineVertexShader* _pVS)
{
	EngineVertexShader* pVS = (EngineVertexShader*)_pVS;
	EngineVertexBuffer* pVB = (EngineVertexBuffer*)_pVB;
	for (size_t i = 0; i < ArrayCount; i++)
	{
		Desc[i].InputSlot = pVB->GetSlotNumber();
	}
	HRESULT Result = DevicePtr->CreateInputLayout(Desc, ArrayCount, pVS->GetShaderByteCode(), pVS->GetShaderByteLength(), &LayoutPtr);
}

void EngineInputLayout::IntoPipeline()
{
	ContextPtr->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	ContextPtr->IASetInputLayout(LayoutPtr);
}

