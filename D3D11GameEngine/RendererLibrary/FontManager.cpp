#include "pch.h"
#include "FontManager.h"
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")

CFontManager::~CFontManager()
{
	for (auto& c : m_mapLayout)
	{
		c.second->Release();
	}
	m_mapLayout.clear();
	m_pDwriteFactory->Release();
	m_pD2D1RenderTarget->Release();
	m_pD2D1Device->Release();
	m_pD2D1DeviceContext->Release();
	m_pBrush->Release();
	m_pArial->Release();
	m_pLayout->Release();
}

void CFontManager::Initialize(ID3D11Device* pDevice, IDXGISurface* pBackBuffer)
{
	D2D1_FACTORY_OPTIONS d2dFactoryOptions = {};
	ID2D1Factory3* pD2dFactory = nullptr;

	if (S_OK != D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory3), &d2dFactoryOptions, (void**)&pD2dFactory))
		__debugbreak();

	IDXGIDevice* pDxgiDevice = nullptr;
	if (S_OK != pDevice->QueryInterface(IID_PPV_ARGS(&pDxgiDevice)))
		__debugbreak();

	if (S_OK != pD2dFactory->CreateDevice(pDxgiDevice, &m_pD2D1Device))
		__debugbreak();

	if (S_OK != m_pD2D1Device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &m_pD2D1DeviceContext))
		__debugbreak();

	D2D1_RENDER_TARGET_PROPERTIES d2dRenderTargetProp =
		D2D1::RenderTargetProperties
		(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
			0.0f,
			0.0f,
			D2D1_RENDER_TARGET_USAGE_NONE,
			D2D1_FEATURE_LEVEL_DEFAULT
		);

	if (S_OK != pD2dFactory->CreateDxgiSurfaceRenderTarget(pBackBuffer, &d2dRenderTargetProp, &m_pD2D1RenderTarget))
		__debugbreak();

	if (S_OK != m_pD2D1RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &m_pBrush))
		__debugbreak();

	if (S_OK != DWriteCreateFactory(DWRITE_FACTORY_TYPE::DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&m_pDwriteFactory))
		__debugbreak();

	UINT dpi = GetDpiForSystem();
	float scaleFactor = (float)dpi / 96.0f;
	if (S_OK != m_pDwriteFactory->CreateTextFormat(L"굴림체", nullptr, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		scaleFactor * 12.0f, L"en-US", &m_pArial))
		__debugbreak();
	
	m_pD2D1RenderTarget->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_ALIASED);
	
	const wchar_t* text = L"게임엔진을 이용해주셔서 감사합니다.";
	UINT32 len = static_cast<UINT32>(wcslen(text));
	if (S_OK != m_pDwriteFactory->CreateTextLayout(text, len, m_pArial, 300.0f, 100.0f, &m_pLayout))
		__debugbreak();

	pDxgiDevice->Release();
	pD2dFactory->Release();
}

void CFontManager::FontRender(const wchar_t* str, float posX, float posY, float width, float height)
{
	IDWriteTextLayout* pTextLayout;
	if (m_mapLayout.find(str) == m_mapLayout.end())
	{
		UINT32 len = static_cast<UINT32>(wcslen(str));

		if (S_OK != m_pDwriteFactory->CreateTextLayout(str, len, m_pArial, width, height, &pTextLayout))
			__debugbreak();

		m_mapLayout.insert({ str,pTextLayout });
	}
	else
	{
		pTextLayout = m_mapLayout[str];
	}
	float halfWinWidth = 1366 * 0.5f;
	float halfWinHeight = 789 * 0.5f;
	m_pD2D1RenderTarget->BeginDraw();
	m_pD2D1RenderTarget->DrawTextLayout(D2D1::Point2F(posX + halfWinWidth, -posY + halfWinHeight), pTextLayout, m_pBrush);
	m_pD2D1RenderTarget->EndDraw();
}

