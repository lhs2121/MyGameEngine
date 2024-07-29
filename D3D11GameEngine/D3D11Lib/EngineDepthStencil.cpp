#include "Pre.h"
#include "EngineDepthStencil.h"

EngineDepthStencil::EngineDepthStencil()
{
}

EngineDepthStencil::~EngineDepthStencil()
{
	if (DepthStencil != nullptr)
	{
		DepthStencil->Release();
	}
}

void EngineDepthStencil::Setting(D3D11_DEPTH_STENCIL_DESC _Desc)
{
	Desc = _Desc;
	DevicePtr->CreateDepthStencilState(&Desc, &DepthStencil);
}

void EngineDepthStencil::IntoPipeline()
{
	ContextPtr->OMSetDepthStencilState(DepthStencil, 1);
}
