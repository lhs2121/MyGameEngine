#include "Pre.h"
#include "EngineRasterizer.h"

EngineRasterizer::EngineRasterizer()
{
}

EngineRasterizer::~EngineRasterizer()
{
	RasterizePtr->Release();
}

void EngineRasterizer::Setting(D3D11_RASTERIZER_DESC _Desc)
{
	Desc = _Desc;
	DevicePtr->CreateRasterizerState(&Desc, &RasterizePtr);
}

void EngineRasterizer::IntoPipeline()
{
	ContextPtr->RSSetState(RasterizePtr);
}
