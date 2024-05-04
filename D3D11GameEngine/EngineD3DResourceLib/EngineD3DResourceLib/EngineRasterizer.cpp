#include "Pre.h"
#include "EngineRasterizer.h"

EngineRasterizer::EngineRasterizer()
{
}

EngineRasterizer::~EngineRasterizer()
{
}

void EngineRasterizer::Release()
{
	RasterizePtr->Release();
}

void EngineRasterizer::IntoPipeLine()
{
	DeviceContext->RSSetState(RasterizePtr);
}
