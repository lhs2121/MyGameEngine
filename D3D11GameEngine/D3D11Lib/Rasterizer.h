#pragma once
#include "D3D11API.h"

class Rasterizer : public IRasterizer
{
public:
	Rasterizer();
	~Rasterizer();

	void Setting(D3D11_RASTERIZER_DESC _Desc) override;
	void IntoPipeline() override;

	ID3D11Device* DevicePtr = nullptr;
	ID3D11DeviceContext* ContextPtr = nullptr;
private:
	D3D11_RASTERIZER_DESC Desc;
	ID3D11RasterizerState* RasterizePtr;
};