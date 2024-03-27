#include "Pre.h"
#include "EngineVertexBuffer.h"


#include <dxgi.h>
#include <D3Dcompiler.h>
#pragma comment(lib, "d3d11")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "D3DCompiler")

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
		&Context
	);


	{
		float4 Size = EngineCore::MainWindow.WinSize;

		DXGI_SWAP_CHAIN_DESC Desc = { 0 };
		Desc.BufferDesc.Width = Size.iX();
		Desc.BufferDesc.Height = Size.iY();
		Desc.BufferDesc.RefreshRate.Numerator = 60;
		Desc.BufferDesc.RefreshRate.Denominator = 1;
		Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		Desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		Desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		Desc.SampleDesc.Count = 1;
		Desc.SampleDesc.Quality = 0;
		Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		Desc.BufferCount = 2;
		Desc.OutputWindow = EngineCore::MainWindow.Hwnd;
		Desc.Windowed = true;
		Desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		Desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		HRESULT Result = FactoryPtr->CreateSwapChain(Device, &Desc, &SwapChain);

		SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&BackBufferTexture));
	}


	{
		HRESULT Result = Device->CreateRenderTargetView(BackBufferTexture, nullptr, &BackBufferRTV);
	}



	FactoryPtr->Release();
	AdapterPtr->Release();
}

void EngineDevice::ResourceInit()
{
	D3D11_BUFFER_DESC Desc;
	D3D11_SUBRESOURCE_DATA Data;
	ID3D11Buffer* VB;

	float4 Rect[] =
	{
		float4(-1.0f, 1.0f, 0.0f,1.0f),
		float4(1.0f, 1.0f, 0.0f,1.0f),
		float4(1.0f, -1.0f, 0.0f,1.0f),
		float4(-1.0f, -1.0f, 0.0f,1.0f),
	};

	Data.pSysMem = Rect;
	Data.SysMemPitch = 0;
	Data.SysMemSlicePitch = 0;

	Desc.ByteWidth = sizeof(float4) * 4;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	Desc.CPUAccessFlags = 0;
	Desc.StructureByteStride = 0;
	Desc.MiscFlags = 0;

	HRESULT Result = Device->CreateBuffer(&Desc, &Data, &VB);
	EngineVertexBuffer NewBuffer;
	NewBuffer.SetResource(0, 1, VB, sizeof(float4), 0);
	Resources.insert(std::make_pair("Rect", &NewBuffer));
}

void EngineDevice::Clear()
{
	const FLOAT ClearColor[4] = { 0.5f, 0.5f, 0.5f, 1 };
	Context->ClearRenderTargetView(BackBufferRTV, ClearColor);
}

void EngineDevice::Present()
{
	SwapChain->Present(0, 0);
}
