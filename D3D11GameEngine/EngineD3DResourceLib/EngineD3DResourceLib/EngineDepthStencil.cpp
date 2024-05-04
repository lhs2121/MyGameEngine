#include "Pre.h"
#include "EngineDepthStencil.h"

EngineDepthStencil::EngineDepthStencil()
{
}

EngineDepthStencil::~EngineDepthStencil()
{
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
	DeviceContext->OMSetDepthStencilState(DepthStencil, 1);
}
