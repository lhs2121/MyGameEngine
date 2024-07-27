#pragma once
#include "D3D11API.h"

class EngineRasterizer : public IEngineRasterizer
{
public:
	EngineRasterizer();
	~EngineRasterizer();

	void Setting(D3D11_RASTERIZER_DESC _Desc) override;
	void IntoPipeLine() override;

private:
	void SetDevice(ID3D11Device* _DevicePtr) override { DevicePtr = _DevicePtr; }
	void SetContext(ID3D11DeviceContext* _ContextPtr) override { ContextPtr = _ContextPtr; }

	ID3D11Device* DevicePtr = nullptr;
	ID3D11DeviceContext* ContextPtr = nullptr;
	D3D11_RASTERIZER_DESC Desc;
	ID3D11RasterizerState* RasterizePtr;
};