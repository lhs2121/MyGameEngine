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

void EngineInputLayout::IntoPipeLine()
{
	m_pDevice->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pDevice->GetContext()->IASetInputLayout(LayoutPtr);
}

