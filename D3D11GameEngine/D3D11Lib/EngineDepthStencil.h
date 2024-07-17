#pragma once
#include "D3D11API.h"

class EngineDepthStencil : public IEngineDepthStencil
{
public:
	// constrcuter destructer
	EngineDepthStencil();
	~EngineDepthStencil();

	// delete Function
	EngineDepthStencil(const EngineDepthStencil& _Other) = delete;
	EngineDepthStencil(EngineDepthStencil&& _Other) noexcept = delete;
	EngineDepthStencil& operator=(const EngineDepthStencil& _Other) = delete;
	EngineDepthStencil& operator=(EngineDepthStencil&& _Other) noexcept = delete;


	void Setting(D3D11_DEPTH_STENCIL_DESC _Desc) override;
	void Release() override;
	void IntoPipeLine();
	void SetDevicePtr(EngineDevice* _DevicePtr)
	{
		DevicePtr = _DevicePtr;
	}
	ID3D11DepthStencilState* GetResource() const
	{
		return DepthStencil;
	};

	EngineDevice* DevicePtr;
	D3D11_DEPTH_STENCIL_DESC Desc;
	ID3D11DepthStencilState* DepthStencil;
};