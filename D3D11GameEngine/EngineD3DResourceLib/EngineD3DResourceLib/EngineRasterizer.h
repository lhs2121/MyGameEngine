#pragma once
#include "IEngineD3DResource.h"

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
	
	void Setting(D3D11_RASTERIZER_DESC _Desc) override;
	void Release() override;
	void IntoPipeLine() override;
	void SetDevicePtr(EngineDevice* _DevicePtr)
	{
		DevicePtr = _DevicePtr;
	}

	EngineDevice* DevicePtr;
	D3D11_RASTERIZER_DESC Desc;
	ID3D11RasterizerState* RasterizePtr;
};