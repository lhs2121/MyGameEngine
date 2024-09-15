#pragma once
#include "ResourceAPI.h"
#include "Windows.h"

class DeviceManager
{
public:
	static DeviceManager* Inst;
	DeviceManager()
	{
		Inst = this;
	}
	~DeviceManager();

	void Init(HWND* pHwnd, float4 WindowSize);
	void InitMesh();
	void InitMaterial();
	void Clear();
	void Present();

	ID3D11Device* mainDevice = nullptr;
	ID3D11DeviceContext* mainContext = nullptr;

	IDXGISwapChain* SwapChain = nullptr;
	ID3D11Texture2D* BackTexture = nullptr;
	ID3D11Texture2D* DepthTexture = nullptr;

	ID3D11RenderTargetView* BackRenderTargetView = nullptr;
	ID3D11DepthStencilView* DepthView = nullptr;
};