#include "Pre.h"
#include "EngineRasterizer.h"

EngineRasterizer::EngineRasterizer()
{
}

EngineRasterizer::~EngineRasterizer()
{
	RasterizePtr->Release();
}

void EngineRasterizer::IntoPipeLine()
{
	Device->GetContext()->RSSetState(RasterizePtr);
}
