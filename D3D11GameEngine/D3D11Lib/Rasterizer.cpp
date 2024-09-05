#include "Pre.h"
#include "Rasterizer.h"

Rasterizer::Rasterizer()
{
}

Rasterizer::~Rasterizer()
{
	RasterizePtr->Release();
}

void Rasterizer::Setting( D3D11_RASTERIZER_DESC _Desc)
{
	Desc = _Desc;
	DevicePtr->CreateRasterizerState(&Desc, &RasterizePtr);
}

void Rasterizer::IntoPipeline()
{
	ContextPtr->RSSetState(RasterizePtr);
}
