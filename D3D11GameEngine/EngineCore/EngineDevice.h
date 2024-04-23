#pragma once
#include "d3d11.h"
#include "EngineD3DResource.h"

class EngineDevice
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

	void Init();
	void ResourceInit();
	void Clear();
	void Present();

	ID3D11Device* GetDevice()
	{
		return Device;
	}
	ID3D11DeviceContext* GetContext()
	{
		return Context;
	}

private:
	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* Context = nullptr;
	IDXGISwapChain* SwapChain = nullptr;

	ID3D11Texture2D* BackTexture = nullptr;
	ID3D11Texture2D* DepthTexture = nullptr; 

	ID3D11RenderTargetView* BackRenderTargetView = nullptr;
	ID3D11DepthStencilView* DepthView = nullptr;
};