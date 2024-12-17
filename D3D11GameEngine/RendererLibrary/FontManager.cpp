#include "pch.h"
#include "FontManager.h"
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")

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
	
	IDWriteFactory* pDwriteFactory = nullptr;

	if (S_OK != DWriteCreateFactory(DWRITE_FACTORY_TYPE::DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&pDwriteFactory))
		__debugbreak();

	if (S_OK != pDwriteFactory->CreateTextFormat(L"굴림체", nullptr, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 23.0f, L"en-US", &m_pArial))
		__debugbreak();


	m_pD2D1RenderTarget->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);

	const wchar_t* text = L"게임엔진을 이용해주셔서 감사합니다.";
	UINT32 len = static_cast<UINT32>(wcslen(text));
	if (S_OK != pDwriteFactory->CreateTextLayout(text, len, m_pArial, 300.0f, 100.0f, &m_pLayout))
		__debugbreak();

	pDxgiDevice->Release();
	pD2dFactory->Release();
}

void CFontManager::FontRender()
{
	m_pD2D1RenderTarget->BeginDraw();
	//m_pD2D1RenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	m_pLayout->SetMaxWidth(10);
	m_pLayout->SetMaxHeight(100);
	m_pD2D1RenderTarget->DrawTextLayout(D2D1::Point2F(50, 50), m_pLayout, m_pBrush);

	m_pLayout->SetMaxWidth(100);
	m_pLayout->SetMaxHeight(10);
	m_pD2D1RenderTarget->DrawTextLayout(D2D1::Point2F(200, 200), m_pLayout, m_pBrush);
	m_pD2D1RenderTarget->EndDraw(); 
}

