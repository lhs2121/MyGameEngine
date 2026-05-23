#include "pch.h"
#include "Renderer.h"

using namespace DirectX;

struct SpriteTransformData
{
	XMMATRIX matWorld;
	XMMATRIX matView;
	XMMATRIX matProjection;
};

Renderer::~Renderer()
{
	delete m_pHelper;

	if (m_pDeviceContext)
		m_pDeviceContext->ClearState();

	m_pDeviceContext->Release();
	m_pSwapChain->Release();
	m_pRenderTargetBuffer->Release();
	m_pDepthStencilBuffer->Release();
	m_pDepthStencilView->Release();
	m_pRenderTargetView->Release();

#if defined(DEBUG) || defined(_DEBUG)
	ID3D11Debug* dxgiDebug;

	if (S_OK == m_pDevice->QueryInterface(IID_PPV_ARGS(&dxgiDebug)))
	{
		dxgiDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
		dxgiDebug->Release();
	}
#endif

	m_pDevice->Release();
}

void Renderer::Initialize(UINT winWidth, UINT winHeight, HWND& hwnd)
{
	IDXGIFactory* pFact = nullptr;
	IDXGIAdapter* pAdap = nullptr;

	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

	CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFact));
	pFact->EnumAdapters(0, &pAdap);

	HRESULT rs = D3D11CreateDevice(pAdap, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN, nullptr,
		D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG, nullptr, 0, D3D11_SDK_VERSION, &m_pDevice, &featureLevel, &m_pDeviceContext);
	if (rs != S_OK)
		__debugbreak();

	{
		DXGI_SWAP_CHAIN_DESC desc = { 0 };
		desc.BufferDesc.Width = winWidth;
		desc.BufferDesc.Height = winHeight;
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
		desc.BufferCount = 2;
		desc.OutputWindow = hwnd;
		desc.Windowed = true;
		desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		if (S_OK != pFact->CreateSwapChain(m_pDevice, &desc, &m_pSwapChain))
			__debugbreak();
	}

	if (S_OK != m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&m_pRenderTargetBuffer)))
		__debugbreak();

	if (S_OK != m_pDevice->CreateRenderTargetView(m_pRenderTargetBuffer, nullptr, &m_pRenderTargetView))
		__debugbreak();


	D3D11_TEXTURE2D_DESC dsbDesc;
	dsbDesc.Width = winWidth;
	dsbDesc.Height = winHeight;
	dsbDesc.MipLevels = 1;
	dsbDesc.ArraySize = 1;
	dsbDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsbDesc.SampleDesc.Count = 1;
	dsbDesc.SampleDesc.Quality = 0;
	dsbDesc.Usage = D3D11_USAGE_DEFAULT;
	dsbDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	dsbDesc.CPUAccessFlags = 0;
	dsbDesc.MiscFlags = 0;

	if (S_OK != m_pDevice->CreateTexture2D(&dsbDesc, nullptr, &m_pDepthStencilBuffer))
		__debugbreak();

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&dsvDesc, sizeof(dsvDesc));
	dsvDesc.Format = dsbDesc.Format;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	if (S_OK != m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, &dsvDesc, &m_pDepthStencilView))
		__debugbreak();

	D3D11_VIEWPORT viewportDesc;
	viewportDesc.Width = (FLOAT)winWidth;
	viewportDesc.Height = (FLOAT)winHeight;
	viewportDesc.MinDepth = 0;
	viewportDesc.MaxDepth = 1;
	viewportDesc.TopLeftX = 0;
	viewportDesc.TopLeftY = 0;
	m_pDeviceContext->RSSetViewports(1, &viewportDesc);

	pFact->Release();
	pAdap->Release();

	m_matView = XMMatrixLookToLH(m_CameraPosition, m_CameraEyeDirection, m_CameraUpDirection);
	m_matProjection = XMMatrixPerspectiveFovLH(m_degFovY * Deg2Rad, (float)winWidth / (float)winHeight, m_near, m_far);

	m_pHelper = new D3DHelper;
	m_pHelper->Initialize(m_pDevice);

	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pDeviceContext->IASetInputLayout(m_pHelper->pLayout);

}

void Renderer::BeginFrame()
{
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, m_clearColor);
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
}

void Renderer::EndFrame()
{
	m_pSwapChain->Present(0, 0);
}

void Renderer::LoadTexture(const WCHAR* textureFile)
{
	m_pHelper->LoadTexture(m_pDevice, textureFile);
}

void Renderer::DrawBlockGrid(const BlockGridDesc& desc)
{
	if (desc.textureFile == nullptr || desc.tiles == nullptr || desc.width <= 0 || desc.height <= 0)
		return;

	ShaderData* shader = m_pHelper->pShaders[L"BasicSprite2DShader.hlsl"];
	ID3D11ShaderResourceView* texture = m_pHelper->pTextures[PathFindFileNameW(desc.textureFile)];

	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	m_pDeviceContext->IASetInputLayout(m_pHelper->pLayout);
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pHelper->pRect2D, &stride, &offset);
	m_pDeviceContext->IASetIndexBuffer(m_pHelper->pRect2DIndex, DXGI_FORMAT_R16_UINT, 0);
	m_pDeviceContext->VSSetShader(shader->m_pVertexShader, nullptr, 0);
	m_pDeviceContext->PSSetShader(shader->m_pPixelShader, nullptr, 0);
	m_pDeviceContext->PSSetShaderResources(0, 1, &texture);
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pHelper->pPoint);
	m_pDeviceContext->RSSetState(m_pHelper->pSolid);
	m_pDeviceContext->OMSetBlendState(m_pHelper->pAlpha, nullptr, 0xFFFFFFFF);
	m_pDeviceContext->OMSetDepthStencilState(m_pHelper->pDepthEnabledState, 0);

	const int atlasColumns = desc.atlasColumns > 0 ? desc.atlasColumns : 1;
	const int atlasRows = desc.atlasRows > 0 ? desc.atlasRows : 1;
	const float uvWidth = 1.0f / atlasColumns;
	const float uvHeight = 1.0f / atlasRows;

	for (int y = 0; y < desc.height; ++y)
	{
		for (int x = 0; x < desc.width; ++x)
		{
			const BlockTile& tile = desc.tiles[y * desc.width + x];
			if (!tile.visible)
				continue;

			const int tileX = tile.tileIndex % atlasColumns;
			const int tileY = tile.tileIndex / atlasColumns;

			SpriteData spriteData;
			spriteData.ratio = { uvWidth, uvHeight };
			spriteData.offset = { tileX * uvWidth, tileY * uvHeight };

			const float posX = desc.originX + x * desc.tileSize;
			const float posY = desc.originY - y * desc.tileSize;
			XMMATRIX world = XMMatrixScaling(desc.tileSize, desc.tileSize, 1.0f) * XMMatrixTranslation(posX, posY, 0.0f);

			SpriteTransformData transformData{ world, m_matView, m_matProjection };
			ConstantBuffer* transformBuffer = D3DHelper::CreateConstantBuffer(m_pDevice, &transformData, sizeof(SpriteTransformData), 0, "vs");
			ConstantBuffer* spriteBuffer = D3DHelper::CreateConstantBuffer(m_pDevice, &spriteData, sizeof(SpriteData), 0, "ps");

			transformBuffer->Bind(m_pDeviceContext);
			spriteBuffer->Bind(m_pDeviceContext);
			m_pDeviceContext->DrawIndexed(6, 0, 0);

			delete transformBuffer;
			delete spriteBuffer;
		}
	}
}

