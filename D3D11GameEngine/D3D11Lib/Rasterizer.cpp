#include "Pre.h"
#include "Rasterizer.h"

Rasterizer::Rasterizer()
{
}

Rasterizer::~Rasterizer()
{
	RasterizePtr->Release();
}

void Rasterizer::Setting(ID3D11Device* DevicePtr, D3D11_RASTERIZER_DESC _Desc)
{
	Desc = _Desc;
	DevicePtr->CreateRasterizerState(&Desc, &RasterizePtr);
}

void Rasterizer::IntoPipeline(ID3D11DeviceContext* ContextPtr)
{
	ContextPtr->RSSetState(RasterizePtr);
}
