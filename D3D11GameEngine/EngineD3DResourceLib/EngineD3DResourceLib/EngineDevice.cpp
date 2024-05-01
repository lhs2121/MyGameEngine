#include "Pre.h"
#include "EngineDevice.h"
#include <dxgi.h>
#include <D3Dcompiler.h>

#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3d11.lib")

EngineDevice::EngineDevice()
{
}

EngineDevice::~EngineDevice()
{
	if (m_pDeviceContext != nullptr)
	{
		m_pDeviceContext->Release();
		m_pDeviceContext = nullptr;
	}
	if (m_pSwapChain != nullptr)
	{
		m_pSwapChain->Release();
		m_pSwapChain = nullptr;
	}
	if (m_pBackTexture != nullptr)
	{
		m_pBackTexture->Release();
		m_pBackTexture = nullptr;
	}
	if (m_pBackRenderTargetView != nullptr)
	{
		m_pBackRenderTargetView->Release();
		m_pBackRenderTargetView = nullptr;
	}
	if (m_pDepthView != nullptr)
	{
		m_pDepthView->Release();
		m_pDepthView = nullptr;
	}
	if (m_pDepthTexture != nullptr)
	{
		m_pDepthTexture->Release();
		m_pDepthTexture = nullptr;
	}
	if (m_pDevice != nullptr)
	{
		//#if defined(DEBUG) || defined(_DEBUG)
		//		ID3D11Debug* dxgiDebug;
		//
		//		if (SUCCEEDED(EngineCore::GetDevice()->QueryInterface(IID_PPV_ARGS(&dxgiDebug))))
		//		{
		//			dxgiDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
		//			dxgiDebug = nullptr;
		//		}
		//#endif

		m_pDevice->Release();
		m_pDevice = nullptr;
	}
}

void EngineDevice::Init()
{
	IDXGIFactory* FactoryPtr = nullptr;
	IDXGIAdapter* AdapterPtr = nullptr;

	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL_11_0;

	CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&FactoryPtr));
	FactoryPtr->EnumAdapters(0, &AdapterPtr);

	HRESULT hr = D3D11CreateDevice
	(
		AdapterPtr,
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN,
		nullptr,
		// xhash internal header
		D3D11_CREATE_DEVICE_DEBUG,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&m_pDevice,
		&Level,
		&m_pDeviceContext
	);

	{
		DXGI_SWAP_CHAIN_DESC Desc = { 0 };
		Desc.BufferDesc.Width = 1920;
		Desc.BufferDesc.Height = 1080;
		Desc.BufferDesc.RefreshRate.Numerator = 60;
		Desc.BufferDesc.RefreshRate.Denominator = 1;
		Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		Desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		Desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		Desc.SampleDesc.Count = 1;
		Desc.SampleDesc.Quality = 0;
		Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
		Desc.BufferCount = 2;
		Desc.OutputWindow = 0;
		Desc.Windowed = true;
		Desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		Desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		HRESULT Result = FactoryPtr->CreateSwapChain(m_pDevice, &Desc, &m_pSwapChain);

		m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&m_pBackTexture));
	}


	{
		HRESULT Result = m_pDevice->CreateRenderTargetView(m_pBackTexture, nullptr, &m_pBackRenderTargetView);
	}

	{
		D3D11_TEXTURE2D_DESC Desc;
		Desc.Width = 1920;
		Desc.Height = 1080;
		Desc.MipLevels = 1;
		Desc.ArraySize = 1;
		Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		Desc.SampleDesc.Count = 1;
		Desc.SampleDesc.Quality = 0;
		Desc.Usage = D3D11_USAGE_DEFAULT;
		Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		Desc.CPUAccessFlags = 0;
		Desc.MiscFlags = 0;

		HRESULT Result = m_pDevice->CreateTexture2D(&Desc, nullptr, &m_pDepthTexture);

		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory(&descDSV, sizeof(descDSV));
		descDSV.Format = Desc.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		// ±íÀÌ ½ºÅÙ½Ç ºä »ý¼º
		if (S_OK != m_pDevice->CreateDepthStencilView(m_pDepthTexture, &descDSV, &m_pDepthView))
		{
			
		}
	}

	{
		D3D11_VIEWPORT Desc;
		Desc.Width = 1920;
		Desc.Height = 1080;
		Desc.MinDepth = 0;
		Desc.MaxDepth = 1;
		Desc.TopLeftX = 0;
		Desc.TopLeftY = 0;
		m_pDeviceContext->RSSetViewports(1, &Desc);
		//ÀÏ´Ü µð¹ÙÀÌ½º ÃÊ±âÈ­ ÇÒ¶§ ºäÆ÷Æ® ¼¼ÆÃÇØÁÜ
	}

	FactoryPtr->Release();
	AdapterPtr->Release();
}

void EngineDevice::Clear()
{
	const FLOAT ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_pDeviceContext->ClearRenderTargetView(m_pBackRenderTargetView, ClearColor);
	m_pDeviceContext->ClearDepthStencilView(m_pDepthView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	m_pDeviceContext->OMSetRenderTargets(1, &m_pBackRenderTargetView, m_pDepthView);
}

void EngineDevice::Present()
{
	m_pSwapChain->Present(0, 0);
}


