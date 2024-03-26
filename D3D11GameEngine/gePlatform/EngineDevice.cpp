#include "Pre.h"
#include "EngineDevice.h"
#include "EngineCore.h"
#include "EngineWindow.h"

#include <dxgi.h>
#include <D3Dcompiler.h>
#pragma comment(lib, "d3d11")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "D3DCompiler")

ID3D11Device*             EngineDevice::Device = nullptr;
ID3D11DeviceContext*      EngineDevice::DeviceContext = nullptr;
IDXGISwapChain*           EngineDevice::SwapChain = nullptr;
ID3D11RenderTargetView*   EngineDevice::RenderTargetView = nullptr;
ID3D11Texture2D*          EngineDevice::BackBufferTexture = nullptr;

EngineDevice::EngineDevice()
{
}

EngineDevice::~EngineDevice()
{
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
		D3D11_CREATE_DEVICE_DEBUG,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&Device,
		&Level,
		&DeviceContext
	);

	//float4 Size = EngineCore::GetMainWindow().WindowSize;

	DXGI_SWAP_CHAIN_DESC Desc = { 0 };
	Desc.BufferDesc.Width = 500;
	Desc.BufferDesc.Height = 500;
	Desc.BufferDesc.RefreshRate.Numerator = 60;
	Desc.BufferDesc.RefreshRate.Denominator = 1;
	Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	Desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	Desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	Desc.BufferCount = 2;
	Desc.OutputWindow = EngineCore::GetMainWindow().Hwnd;
	Desc.Windowed = true;
	Desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	Desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	FactoryPtr->CreateSwapChain(Device, &Desc, &SwapChain);

	SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&BackBufferTexture));

	Device->CreateRenderTargetView(BackBufferTexture, nullptr, &RenderTargetView);

	FactoryPtr->Release();
	AdapterPtr->Release();
}
