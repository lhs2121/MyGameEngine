#include <d3d11.h>
#include <dxgi.h>
#include <D3Dcompiler.h>
#include "Pre.h"
#include "EngineRenderer.h"
#include "EngineCore.h"

#pragma comment(lib, "d3d11")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "D3DCompiler")


EngineRenderer::EngineRenderer()
{
}

void EngineRenderer::Init()
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
	scDesc.OutputWindow = EngineCore::GetMainWindow().GetHwnd();
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

void EngineRenderer::CreatMesh()
{
}

void EngineRenderer::CreateVertexBuffer()
{
	struct SimpleVertex
	{
		float4 Pos;
	};

	SimpleVertex vertices[]
	{
		float4(-0.5f,0.5f),
		float4(0.5f, 0.5f),
		float4(0.5f, -0.5f),
		float4(-0.5f, -0.5f),
	};

	D3D11_BUFFER_DESC VBDesc = { 0 };
	VBDesc.ByteWidth = 16;
	VBDesc.Usage = D3D11_USAGE_DEFAULT;
	VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VBDesc.CPUAccessFlags = 0;
	VBDesc.MiscFlags = 0;
	VBDesc.StructureByteStride = 4;

	D3D11_SUBRESOURCE_DATA VBSubData = { 0 };
	VBSubData.pSysMem = vertices;
	VBSubData.SysMemPitch = 0;
	VBSubData.SysMemSlicePitch = 0;

	ID3D11Buffer* VB;
	device->CreateBuffer(&VBDesc, &VBSubData, &VB);

	UINT stride = 12;
	UINT offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &VB, &stride, &offset);
}

void EngineRenderer::CreateIndexBuffer()
{
	UINT indices[]
	{
		0,1,2,
		2,3,0
	};

	D3D11_BUFFER_DESC IBDesc = { 0 };
	IBDesc.ByteWidth = 24;
	IBDesc.Usage = D3D11_USAGE_DEFAULT;
	IBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IBDesc.CPUAccessFlags = 0;
	IBDesc.MiscFlags = 0;
	IBDesc.StructureByteStride = 4;

	D3D11_SUBRESOURCE_DATA IBSubData = { 0 };
	IBSubData.pSysMem = indices;
	IBSubData.SysMemPitch = 0;
	IBSubData.SysMemSlicePitch = 0;

	ID3D11Buffer* IB;
	device->CreateBuffer(&IBDesc, &IBSubData, &IB);
	deviceContext->IASetIndexBuffer(IB, DXGI_FORMAT_R32_UINT, 0);
}

void EngineRenderer::CreateVertexShader()
{
	ID3DBlob* shaderBlob;
	ID3DBlob* errorBlob;
	HRESULT hr = D3DCompileFromFile(L"VertexShader.hlsl", 0, 0, "main", "vs_5_0", 0, 0, &shaderBlob, &errorBlob);

	ID3D11VertexShader* Shader;
	device->CreateVertexShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &Shader);
	deviceContext->VSSetShader(Shader, nullptr, 0);
}

void EngineRenderer::Render()
{
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	CreateVertexBuffer();
	CreateIndexBuffer();
	CreateVertexShader();

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->OMSetRenderTargets(1, &renderTargetViews[0], nullptr);
	deviceContext->ClearRenderTargetView(renderTargetViews[0], clearColor);
	deviceContext->DrawIndexed(6,0,0);
	swapChain->Present(0, 0);
}
