#pragma once
#include "EngineD3DInterface.h"

class EngineDevice : public IEngineDevice
{
public:
	// constrcuter destructer
	EngineDevice();
	~EngineDevice();

	// delete Function
	EngineDevice(const EngineDevice& _Other) = delete;
	EngineDevice(EngineDevice&& _Other) noexcept = delete;
	EngineDevice& operator=(const EngineDevice& _Other) = delete;
	EngineDevice& operator=(EngineDevice&& _Other) noexcept = delete;

	void Init(void* pHwnd,float4 WindowSize) override;
	void ResourceInit(void* pManager) override;
	void Clear() override;
	void Present() override;
	void Release() override;
	ID3D11Device* GetDevice() override
	{
		return Device;
	}
	ID3D11DeviceContext* GetContext() override
	{
		return DeviceContext;
	}

private:
	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* DeviceContext = nullptr;
	IDXGISwapChain* SwapChain = nullptr;

	ID3D11Texture2D* BackTexture = nullptr;
	ID3D11Texture2D* DepthTexture = nullptr; 

	ID3D11RenderTargetView* BackRenderTargetView = nullptr;
	ID3D11DepthStencilView* DepthView = nullptr;
};