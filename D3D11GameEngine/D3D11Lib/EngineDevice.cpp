#include "Pre.h"
#include "EngineDevice.h"

EngineDevice::EngineDevice()
{
}

EngineDevice::~EngineDevice()
{
	if (ContextPtr != nullptr)
	{
		ContextPtr->Release();
		ContextPtr = nullptr;
	}
	if (SwapChain != nullptr)
	{
		SwapChain->Release();
		SwapChain = nullptr;
	}
	if (BackTexture != nullptr)
	{
		BackTexture->Release();
		BackTexture = nullptr;
	}
	if (BackRenderTargetView != nullptr)
	{
		BackRenderTargetView->Release();
		BackRenderTargetView = nullptr;
	}
	if (DepthView != nullptr)
	{
		DepthView->Release();
		DepthView = nullptr;
	}
	if (DepthTexture != nullptr)
	{
		DepthTexture->Release();
		DepthTexture = nullptr;
	}
	if (DevicePtr != nullptr)
	{
		#if defined(DEBUG) || defined(_DEBUG)
				ID3D11Debug* dxgiDebug;
		
				if (DevicePtr->QueryInterface(IID_PPV_ARGS(&dxgiDebug)))
				{
					dxgiDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
					dxgiDebug = nullptr;
				}
		#endif

		DevicePtr->Release();
		DevicePtr = nullptr;
	}
}

void EngineDevice::Init(void* pHwnd, float4 WindowSize)
{
	HWND* CastPtr = (HWND*)pHwnd;
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
		&DevicePtr,
		&Level,
		&ContextPtr
	);

	{
		DXGI_SWAP_CHAIN_DESC Desc = { 0 };
		Desc.BufferDesc.Width = WindowSize.ix();
		Desc.BufferDesc.Height = WindowSize.iy();
		Desc.BufferDesc.RefreshRate.Numerator = 60;
		Desc.BufferDesc.RefreshRate.Denominator = 1;
		Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		Desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		Desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		Desc.SampleDesc.Count = 1;
		Desc.SampleDesc.Quality = 0;
		Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
		Desc.BufferCount = 2;
		Desc.OutputWindow = *CastPtr;
		Desc.Windowed = true;
		Desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		Desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		HRESULT Result = FactoryPtr->CreateSwapChain(DevicePtr, &Desc, &SwapChain);

		SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&BackTexture));
	}


	{
		HRESULT Result = DevicePtr->CreateRenderTargetView(BackTexture, nullptr, &BackRenderTargetView);
	}

	{
		D3D11_TEXTURE2D_DESC Desc;
		Desc.Width = WindowSize.ix();
		Desc.Height = WindowSize.iy();
		Desc.MipLevels = 1;
		Desc.ArraySize = 1;
		Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		Desc.SampleDesc.Count = 1;
		Desc.SampleDesc.Quality = 0;
		Desc.Usage = D3D11_USAGE_DEFAULT;
		Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		Desc.CPUAccessFlags = 0;
		Desc.MiscFlags = 0;

		HRESULT Result = DevicePtr->CreateTexture2D(&Desc, nullptr, &DepthTexture);

		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory(&descDSV, sizeof(descDSV));
		descDSV.Format = Desc.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		// ±íÀÌ ½ºÅÙ½Ç ºä »ý¼º
		if (S_OK != DevicePtr->CreateDepthStencilView(DepthTexture, &descDSV, &DepthView))
		{
		}
	}

	{
		D3D11_VIEWPORT Desc;
		Desc.Width = WindowSize.x;
		Desc.Height = WindowSize.y;
		Desc.MinDepth = 0;
		Desc.MaxDepth = 1;
		Desc.TopLeftX = 0;
		Desc.TopLeftY = 0;
		ContextPtr->RSSetViewports(1, &Desc);
		//ÀÏ´Ü µð¹ÙÀÌ½º ÃÊ±âÈ­ ÇÒ¶§ ºäÆ÷Æ® ¼¼ÆÃÇØÁÜ
	}

	FactoryPtr->Release();
	AdapterPtr->Release();
}

void EngineDevice::Clear()
{
	const FLOAT ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	ContextPtr->ClearRenderTargetView(BackRenderTargetView, ClearColor);
	ContextPtr->ClearDepthStencilView(DepthView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	ContextPtr->OMSetRenderTargets(1, &BackRenderTargetView, DepthView);
}

void EngineDevice::Present()
{
	SwapChain->Present(0, 0);
}
