#pragma once
#include <d3d11.h>
#include <vector>
class MyRenderer
{
public:
	MyRenderer() { Inst = this; }
	~MyRenderer() 
	{
		device->Release();
		deviceContext->Release();
		swapChain->Release();
		renderTargetView->Release();
		backBufferTexture->Release();
	};
	MyRenderer(const MyRenderer& _Other) = delete;
	MyRenderer(MyRenderer&& _Other) noexcept = delete;
	MyRenderer& operator=(const MyRenderer& _Other) = delete;
	MyRenderer& operator=(MyRenderer&& _Other) noexcept = delete;

	static MyRenderer* Inst;


	void Render();
	void Init();

	void CreateMesh();
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

