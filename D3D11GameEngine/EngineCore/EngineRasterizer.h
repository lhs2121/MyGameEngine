#pragma once
#include "EngineD3DResource.h"

class EngineRasterizer : public EngineD3DResource<EngineRasterizer>
{
public:
	// constrcuter destructer
	EngineRasterizer();
	~EngineRasterizer();

	// delete Function
	EngineRasterizer(const EngineRasterizer& _Other) = delete;
	EngineRasterizer(EngineRasterizer&& _Other) noexcept = delete;
	EngineRasterizer& operator=(const EngineRasterizer& _Other) = delete;
	EngineRasterizer& operator=(EngineRasterizer&& _Other) noexcept = delete;

	void CreateResource(D3D11_RASTERIZER_DESC _Desc);
	void IntoPipeLine() override;

private:
	D3D11_RASTERIZER_DESC Desc;
	ID3D11RasterizerState* RasterizePtr;
};