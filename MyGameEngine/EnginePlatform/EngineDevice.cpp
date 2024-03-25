#include "Pre.h"
#include "EngineDevice.h"
#include "EngineCore.h"
#include "EngineWindow.h"

#include <dxgi.h>
#include <D3Dcompiler.h>
#pragma comment(lib, "d3d11")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "D3DCompiler")

ID3D11Device*             EngineDevice::e_Device = nullptr;
ID3D11DeviceContext*      EngineDevice::e_DeviceContext = nullptr;
IDXGISwapChain*           EngineDevice::e_SwapChain = nullptr;
ID3D11RenderTargetView*   EngineDevice::e_RenderTargetView = nullptr;
ID3D11Texture2D*          EngineDevice::e_BackBufferTexture = nullptr;

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
		&e_Device,
		&Level,
		&e_DeviceContext
	);

	float4 Size = EngineCore::GetMainWindow().WindowSize;

	DXGI_SWAP_CHAIN_DESC Desc = { 0 };
	Desc.BufferDesc.Width = Size.X;
	Desc.BufferDesc.Height = Size.Y;
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

	FactoryPtr->CreateSwapChain(e_Device, &Desc, &e_SwapChain);

	e_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&e_BackBufferTexture));

	e_Device->CreateRenderTargetView(e_BackBufferTexture, nullptr, &e_RenderTargetView);

	FactoryPtr->Release();
	AdapterPtr->Release();
}
