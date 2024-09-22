#include "Pre.h"
#include "DeviceManager.h"

DeviceManager* DeviceManager::Inst = nullptr;

DeviceManager::~DeviceManager()
{
	if (mainContext != nullptr)
	{
		mainContext->Release();
		mainContext = nullptr;
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
	if (mainDevice != nullptr)
	{
//#if defined(DEBUG) || defined(_DEBUG)
//		ID3D11Debug* dxgiDebug;
//
//		if (S_OK == mainDevice->QueryInterface(IID_PPV_ARGS(&dxgiDebug)))
//		{
//			dxgiDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
//			dxgiDebug = nullptr;
//		}
//#endif

		mainDevice->Release();
		mainDevice = nullptr;
	}
}

void DeviceManager::Init(HWND* pHwnd, float4 WindowSize)
{
	IDXGIFactory* FactoryPtr = nullptr;
	IDXGIAdapter* AdapterPtr = nullptr;

	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL_11_0;

	CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&FactoryPtr));
	FactoryPtr->EnumAdapters(0, &AdapterPtr);

	if (S_OK != D3D11CreateDevice
	(
		AdapterPtr,
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&mainDevice,
		&Level,
		&mainContext
	))
	{
		Debug::MsgBoxAssert("디바이스 생성 실패");
	}

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
		Desc.OutputWindow = *pHwnd;
		Desc.Windowed = true;
		Desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		Desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		if (S_OK != FactoryPtr->CreateSwapChain(mainDevice, &Desc, &SwapChain))
		{
			Debug::MsgBoxAssert("스왑체인 생성 실패");
		}

		SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&BackTexture));
	}



	if (S_OK != mainDevice->CreateRenderTargetView(BackTexture, nullptr, &BackRenderTargetView))
	{
		Debug::MsgBoxAssert("백버퍼 렌더타겟 생성 실패");
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

		HRESULT Result = mainDevice->CreateTexture2D(&Desc, nullptr, &DepthTexture);

		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory(&descDSV, sizeof(descDSV));
		descDSV.Format = Desc.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		// 깊이 스텐실 뷰 생성
		if (S_OK != mainDevice->CreateDepthStencilView(DepthTexture, &descDSV, &DepthView))
		{
			Debug::MsgBoxAssert("뎁스스텐실 생성 실패");
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
		mainContext->RSSetViewports(1, &Desc);
		//일단 디바이스 초기화 할때 뷰포트 세팅해줌
	}

	FactoryPtr->Release();
	AdapterPtr->Release();
}

void DeviceManager::Clear()
{
	mainContext->ClearRenderTargetView(BackRenderTargetView, clearColor);
	mainContext->ClearDepthStencilView(DepthView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	mainContext->OMSetRenderTargets(1, &BackRenderTargetView, DepthView);
}

void DeviceManager::Present()
{
	SwapChain->Present(0, 0);
}
