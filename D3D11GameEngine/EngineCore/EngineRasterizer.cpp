#include "Pre.h"
#include "EngineRasterizer.h"

EngineRasterizer::EngineRasterizer()
{
}

EngineRasterizer::~EngineRasterizer()
{
}

void EngineRasterizer::CreateResource(D3D11_RASTERIZER_DESC _Desc)
{
	Desc = _Desc;
	EngineCore::GetDevice()->CreateRasterizerState(&Desc, &RasterizePtr);
}

void EngineRasterizer::IntoPipeLine()
{
	EngineCore::GetContext()->RSSetState(RasterizePtr);
}
