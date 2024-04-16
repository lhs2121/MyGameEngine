#include "Pre.h"
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"
#include "EngineInputLayout.h"
#include "EngineVertexShader.h"
#include "EnginePixelShader.h"

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
	if (Device != nullptr)
	{
		Device->Release();
		Device = nullptr;
	}
	if (Context != nullptr)
	{
		Context->Release();
		Context = nullptr;
	}
	if (SwapChain != nullptr)
	{
		SwapChain->Release();
		SwapChain = nullptr;
	}
	if (BackBufferTexture != nullptr)
	{
		BackBufferTexture->Release();
		BackBufferTexture = nullptr;
	}
	if (BackBufferRTV != nullptr)
	{
		BackBufferRTV->Release();
		BackBufferRTV = nullptr;
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
		&Device,
		&Level,
		&Context
	);

	{
		float4 Size = EngineCore::GetMainWindow().GetWindowSize();

		DXGI_SWAP_CHAIN_DESC Desc = { 0 };
		Desc.BufferDesc.Width = Size.ix();
		Desc.BufferDesc.Height = Size.iy();
		Desc.BufferDesc.RefreshRate.Numerator = 60;
		Desc.BufferDesc.RefreshRate.Denominator = 1;
		Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		Desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		Desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		Desc.SampleDesc.Count = 1;
		Desc.SampleDesc.Quality = 0;
		Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		Desc.BufferCount = 2;
		Desc.OutputWindow = EngineCore::GetMainWindow().GetHwnd();
		Desc.Windowed = true;
		Desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		Desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		HRESULT Result = FactoryPtr->CreateSwapChain(Device, &Desc, &SwapChain);

		SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&BackBufferTexture));
	}


	{
		HRESULT Result = Device->CreateRenderTargetView(BackBufferTexture, nullptr, &BackBufferRTV);
	}

	{
		D3D11_VIEWPORT Desc;
		Desc.Width = EngineCore::GetMainWindow().GetWindowSize().x;
		Desc.Height = EngineCore::GetMainWindow().GetWindowSize().y;
		Desc.MaxDepth = 1;
		Desc.MinDepth = 0;
		Desc.TopLeftX = 0;
		Desc.TopLeftY = 0;
		Context->RSSetViewports(1, &Desc);
		//일단 디바이스 초기화 할때 뷰포트 세팅해줌
	}

	FactoryPtr->Release();
	AdapterPtr->Release();
}

void EngineDevice::ResourceInit()
{
	EngineDirectory Dir;
	Dir.GoParent();
	Dir.GoChild("EngineShader");
	std::vector<EngineFile> AllShaderFile = Dir.GetAllFile(".hlsl");

	for (EngineFile& ShaderFile : AllShaderFile)
	{
		std::string FileName = ShaderFile.GetFileName();
		EngineVertexShader* NewVS = EngineVertexShader::CreateResource(FileName);
		EnginePixelShader* NewPS = EnginePixelShader::CreateResource(FileName);

		NewVS->ShaderLoad(FileName, ShaderFile.GetStringPath());
		NewPS->ShaderLoad(FileName, ShaderFile.GetStringPath());

		D3D11_INPUT_ELEMENT_DESC Layouts[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		EngineInputLayout* NewRes = EngineInputLayout::CreateResource("Pos");

		NewRes->SetResource(Layouts, 1, NewVS->GetShaderByteCode(), NewVS->GetShaderByteLength());
	}

	std::string path = Dir.GetStringPath();

	{
		float4 Rect[] =
		{
			float4(-0.5f, 0.5f),
			float4(0.5f, 0.5f),
			float4(0.5f, -0.5f),
			float4(-0.5f, -0.5f),
		};
		EngineVertexBuffer* NewRes = EngineVertexBuffer::CreateResource("Rect");
		NewRes->SetResource(Rect, sizeof(float4) * 4);
	}

	{
		UINT Rect[]
		{
			0,1,2,
			2,3,0
		};
		EngineIndexBuffer* NewRes = EngineIndexBuffer::CreateResource("Rect");
		NewRes->SetResource(Rect, sizeof(UINT) * 6);
	}
}

void EngineDevice::Clear()
{
	const FLOAT ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	Context->ClearRenderTargetView(BackBufferRTV, ClearColor);
	Context->OMSetRenderTargets(1, &BackBufferRTV, nullptr);
}

void EngineDevice::Present()
{
	SwapChain->Present(0, 0);
}
