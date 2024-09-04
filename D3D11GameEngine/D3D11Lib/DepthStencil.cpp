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

void DepthStencil::Setting(ID3D11Device* DevicePtr, D3D11_DEPTH_STENCIL_DESC _Desc)
{
	Desc = _Desc;
	DevicePtr->CreateDepthStencilState(&Desc, &StatePtr);
}

void DepthStencil::IntoPipeline(ID3D11DeviceContext* ContextPtr)
{
	ContextPtr->OMSetDepthStencilState(StatePtr, 1);
}
