#pragma once
#include "IEngineD3DRes.h"
#include "EngineD3DResourceManger.h"
#include "d3d11.h"

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

	void Init();
	void ResourceInit();
	void Clear() override;
	void Present() override;

	ID3D11Device* GetDevice() override
	{
		return m_pDevice;
	}
	ID3D11DeviceContext* GetContext() override
	{
		return m_pDeviceContext;
	}

	void SetManager(EngineD3DResourceManger* pManager)
	{
		m_pManager = pManager;
	}
private:
	ID3D11Device* m_pDevice = nullptr;
	ID3D11DeviceContext* m_pDeviceContext = nullptr;
	IDXGISwapChain* m_pSwapChain = nullptr;

	ID3D11Texture2D* m_pBackTexture = nullptr;
	ID3D11Texture2D* m_pDepthTexture = nullptr; 

	ID3D11RenderTargetView* m_pBackRenderTargetView = nullptr;
	ID3D11DepthStencilView* m_pDepthView = nullptr;

	EngineD3DResourceManger* m_pManager = nullptr;

};