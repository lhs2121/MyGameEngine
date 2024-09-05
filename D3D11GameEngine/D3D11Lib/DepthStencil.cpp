#include "Pre.h"
#include "DepthStencil.h"
#include "ResManager.h"
#include "Device.h"

DepthStencil::DepthStencil()
{
}

DepthStencil::~DepthStencil()
{
	if (StatePtr != nullptr)
	{
		StatePtr->Release();
	}
}

void DepthStencil::Setting(D3D11_DEPTH_STENCIL_DESC _Desc)
{
	Desc = _Desc;
	DevicePtr->CreateDepthStencilState(&Desc, &StatePtr);
}

void DepthStencil::IntoPipeline()
{
	ContextPtr->OMSetDepthStencilState(StatePtr, 1);
}
