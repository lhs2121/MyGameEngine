#pragma once
#include "d3d11.h"
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

	static void Init();

private:
	static ID3D11Device* e_Device;
	static ID3D11DeviceContext* e_DeviceContext;
	static IDXGISwapChain* e_SwapChain;
	static ID3D11RenderTargetView* e_RenderTargetView;
	static ID3D11Texture2D* e_BackBufferTexture;
};