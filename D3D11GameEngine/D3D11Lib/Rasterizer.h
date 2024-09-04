#pragma once
#include "D3D11API.h"

class Rasterizer : public IRasterizer
{
public:
	Rasterizer();
	~Rasterizer();

	void Setting(ID3D11Device* DevicePtr, D3D11_RASTERIZER_DESC _Desc) override;
	void IntoPipeline(ID3D11DeviceContext* ContextPtr) override;

private:
	D3D11_RASTERIZER_DESC Desc;
	ID3D11RasterizerState* RasterizePtr;
};