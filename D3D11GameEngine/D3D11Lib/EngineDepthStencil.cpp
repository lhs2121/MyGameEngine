#include "Pre.h"
#include "EngineDepthStencil.h"

EngineDepthStencil::EngineDepthStencil()
{
}

EngineDepthStencil::~EngineDepthStencil()
{
}

void EngineDepthStencil::Setting(D3D11_DEPTH_STENCIL_DESC _Desc)
{
	Desc = _Desc;
	DevicePtr->GetDevice()->CreateDepthStencilState(&Desc, &DepthStencil);
}

void EngineDepthStencil::Release()
{
	if (DepthStencil != nullptr)
	{
		DepthStencil->Release();
	}
}

void EngineDepthStencil::IntoPipeLine()
{
	DevicePtr->GetContext()->OMSetDepthStencilState(DepthStencil, 1);
}
