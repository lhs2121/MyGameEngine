#include <d3d11.h>
#include <dxgi.h>
#include "MyRenderer.h"
#include "MyWindow.h"

#pragma comment(lib, "d3d11")
#pragma comment(lib, "dxgi")

MyRenderer* MyRenderer::Inst;


void MyRenderer::Init()
{
	IDXGIFactory* pFact = nullptr;
	IDXGIAdapter* pAdap = nullptr;
	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL_11_0;

	CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pFact));
	pFact->EnumAdapters(0, &pAdap);

	HRESULT hr = D3D11CreateDevice
	(
		pAdap,
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&device,
		&Level,
		&deviceContext
	);

	DXGI_SWAP_CHAIN_DESC scDesc = { 0 };

	scDesc.BufferDesc.Width = 800;
	scDesc.BufferDesc.Height = 600;
	scDesc.BufferDesc.RefreshRate.Numerator = 60;
	scDesc.BufferDesc.RefreshRate.Denominator = 1;
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scDesc.SampleDesc.Count = 1;
	scDesc.SampleDesc.Quality = 0;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.BufferCount = 2;
	scDesc.OutputWindow = MyWindow::Inst->GetHwnd();
	scDesc.Windowed = true;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	scDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	pFact->CreateSwapChain(device, &scDesc, &swapChain);

	pFact->Release();
	pAdap->Release();

	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBufferTexture));

	device->CreateRenderTargetView(backBufferTexture, nullptr, &renderTargetView);

	renderTargetViews.push_back(renderTargetView);
}

void MyRenderer::Render()
{
	float clearColor[4] = { 0.0f, 1.0f, 1.0f, 1.0f };

	deviceContext->ClearRenderTargetView(renderTargetViews[0], clearColor);
	deviceContext->OMSetRenderTargets(1, &renderTargetViews[0], nullptr);
	swapChain->Present(0, 0);
}
// branch000 push