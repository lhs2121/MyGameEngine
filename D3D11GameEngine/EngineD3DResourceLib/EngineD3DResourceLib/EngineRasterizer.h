#pragma once
#include "IEngineD3DRes.h"

class EngineRasterizer : public IEngineRasterizer
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
	
	void IntoPipeLine() override;
	void SetDevicePtr(IEngineDevice* pDevice)
	{
		m_pDevice = pDevice;
	}
	IEngineDevice* m_pDevice;
	D3D11_RASTERIZER_DESC Desc;
	ID3D11RasterizerState* RasterizePtr;
};