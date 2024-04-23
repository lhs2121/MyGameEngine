#include "Pre.h"
#include "EngineDepthStencil.h"

EngineDepthStencil::EngineDepthStencil()
{
}

EngineDepthStencil::~EngineDepthStencil()
{
	if (DepthStencilPtr != nullptr)
	{
		DepthStencilPtr->Release();
	}
}

void EngineDepthStencil::CreateResource(D3D11_DEPTH_STENCIL_DESC _Desc)
{
	Desc = _Desc;
	EngineCore::GetDevice()->CreateDepthStencilState(&Desc, &DepthStencilPtr);
}

void EngineDepthStencil::IntoPipeLine()
{
	EngineCore::GetContext()->OMSetDepthStencilState(DepthStencilPtr, 1);
}
