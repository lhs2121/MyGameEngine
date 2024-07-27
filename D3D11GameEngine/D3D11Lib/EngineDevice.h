#pragma once
#include "D3D11API.h"

class EngineDevice : public IEngineDevice
{
public:
	EngineDevice();
	~EngineDevice();

	void Init(void* pHwnd, float4 WindowSize) override;
	void ResourceInit(IEngineD3DManager* pManager) override;
	void Clear() override;
	void Present() override;
	ID3D11Device* GetDevice() override { return DevicePtr; }
	ID3D11DeviceContext* GetContext() override { return ContextPtr; }

private:
	ID3D11Device* DevicePtr = nullptr;
	ID3D11DeviceContext* ContextPtr = nullptr;
	IDXGISwapChain* SwapChain = nullptr;

	ID3D11Texture2D* BackTexture = nullptr;
	ID3D11Texture2D* DepthTexture = nullptr;

	ID3D11RenderTargetView* BackRenderTargetView = nullptr;
	ID3D11DepthStencilView* DepthView = nullptr;
};