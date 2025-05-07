#pragma once
#include "Interface.h"
#include "ConstantBuffer.h"
#include "FontManager.h"
#include "FBXLoader.h"
#include "D3DHelper.h"

class Renderer : public IRenderer
{
public:
	~Renderer();
	void Initialize(UINT winWidth, UINT winHeight, HWND& hwnd) override;
	void StartRender() override;
	void EndRender() override;

	void LoadTexture(const WCHAR* texPath) override;
private:
	FBXLoader* m_pFBXLoader;
	FontManager* m_pFontManager;
	D3DHelper* m_pHelper;

	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
	IDXGISwapChain* m_pSwapChain;
	ID3D11Texture2D* m_pRenderTargetBuffer;
	ID3D11Texture2D* m_pDepthStencilBuffer;
	ID3D11DepthStencilView* m_pDepthStencilView;
	ID3D11RenderTargetView* m_pRenderTargetView;

	FLOAT m_clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	XMMATRIX m_matView;
	XMMATRIX m_matProjection;

	XMVECTOR m_cameraPosition = { 0.0f, 0.0f, -500.0f, 1.0f };
	XMVECTOR m_cameraEyeDirection = { 0.0f ,0.0f, 1.0f, 1.0f };
	XMVECTOR m_cameraUpDirection = { 0.0f ,1.0f, 0.0f, 1.0f };

	std::unordered_map<const WCHAR*, ID3D11ShaderResourceView*> m_textureList;
	float m_degFovY = 60.0f;
	float m_near = 0.3f;
	float m_far = 1000.0f;
};