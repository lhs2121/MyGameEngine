#pragma once
#include <d3d11.h>
#include <vector>

class EngineRenderer
{
public:
	EngineRenderer();
	~EngineRenderer() 
	{
		device->Release();
		deviceContext->Release();
		swapChain->Release();
		renderTargetView->Release();
		backBufferTexture->Release();
	};
	EngineRenderer(const EngineRenderer& _Other) = delete;
	EngineRenderer(EngineRenderer&& _Other) noexcept = delete;
	EngineRenderer& operator=(const EngineRenderer& _Other) = delete;
	EngineRenderer& operator=(EngineRenderer&& _Other) noexcept = delete;

	void Render();
	void Init();

	void CreatMesh();
	void CreateVertexBuffer();
	void CreateIndexBuffer();
	void CreateVertexShader();
private:
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* deviceContext = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* renderTargetView = nullptr;
	ID3D11Texture2D* backBufferTexture = nullptr;

	std::vector<ID3D11RenderTargetView*> renderTargetViews;
};

