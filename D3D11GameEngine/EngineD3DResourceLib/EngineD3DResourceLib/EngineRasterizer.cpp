#include "Pre.h"
#include "EngineRasterizer.h"

EngineRasterizer::EngineRasterizer()
{
}

EngineRasterizer::~EngineRasterizer()
{
}

void EngineRasterizer::Setting(D3D11_RASTERIZER_DESC _Desc)
{
	Desc = _Desc;
	DevicePtr->GetDevice()->CreateRasterizerState(&Desc, &RasterizePtr);
}

void EngineRasterizer::Release()
{
	RasterizePtr->Release();
}

void EngineRasterizer::IntoPipeLine()
{
	DevicePtr->GetContext()->RSSetState(RasterizePtr);
}
