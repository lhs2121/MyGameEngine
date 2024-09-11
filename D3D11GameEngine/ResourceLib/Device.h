#pragma once
#include "ResourceAPI.h"

class Device : public IDevice
{
public:
	static ID3D11Device* mainDevice;
	static ID3D11DeviceContext* mainContext;
	Device();
	~Device();

	void Init(void* pHwnd, float4 WindowSize) override;
	void InitMesh() override;
	void InitMaterial() override;
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