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

	void Init();
	void Clear();
	void Present();

	/*void SetClearColor(float4 Value)
	{
		ClearColor = Value;
	}*/
private:
	//float4 ClearColor = { 0,0,0,1 };
	ID3D11Device*           Device            = nullptr;
	ID3D11DeviceContext*    Context           = nullptr;
	IDXGISwapChain*         SwapChain         = nullptr;
	ID3D11Texture2D*        BackBufferTexture = nullptr;
	ID3D11RenderTargetView* BackBufferRTV     = nullptr;
};