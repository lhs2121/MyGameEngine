#include "pch.h"
#include "FontManager.h"
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")

void CFontManager::Initialize(ID3D11Device* pDevice, IDXGISurface* pBackBuffer)
{
	D2D1_FACTORY_OPTIONS d2dFactoryOptions = {};
	ID2D1Factory3* pD2DFactory = nullptr;

	if (S_OK != D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory3), &d2dFactoryOptions, (void**)&pD2DFactory))
		__debugbreak();

	IDXGIDevice* pDXGIDevice = nullptr;
	if (S_OK != pDevice->QueryInterface(IID_PPV_ARGS(&pDXGIDevice)))
		__debugbreak();

	if (S_OK != pD2DFactory->CreateDevice(pDXGIDevice, &m_pD2D1Device))
		__debugbreak();

	if (S_OK != m_pD2D1Device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &m_pD2D1DeviceContext))
		__debugbreak();

	D2D1_RENDER_TARGET_PROPERTIES prop =
		D2D1::RenderTargetProperties
		(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
			0.0f,
			0.0f,
			D2D1_RENDER_TARGET_USAGE_NONE,
			D2D1_FEATURE_LEVEL_DEFAULT
		);

	if (S_OK != pD2DFactory->CreateDxgiSurfaceRenderTarget(pBackBuffer, &prop, &m_pD2D1RenderTarget))
		__debugbreak();

	if (S_OK != m_pD2D1RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBrush))
		__debugbreak();

	IDWriteFactory* pDwriteFactory = nullptr;

	if (S_OK != DWriteCreateFactory(DWRITE_FACTORY_TYPE::DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&pDwriteFactory))
		__debugbreak();

	if (S_OK != pDwriteFactory->CreateTextFormat(L"Arial", nullptr, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 24.0f, L"en-US", &m_pArial))
		__debugbreak();

	pDwriteFactory->CreateTextLayout()
	pDXGIDevice->Release();
	pD2DFactory->Release();
}

//BOOL		bResult = FALSE;
//
//m_D2DBitmapWidth = TexWidth;
//m_D2DBitmapHeight = TexHeight;
//
////InitCustomFont(pCustomFontList, dwCustomFontNum);
//
//D2D1_SIZE_U	size;
//size.width = TexWidth;
//size.height = TexHeight;
//
//D2D1_BITMAP_PROPERTIES1 bitmapProperties =
//BitmapProperties1(
//	D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
//	D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
//	fDPI,
//	fDPI
//);
//
//if (FAILED(m_pD2DDeviceContext->CreateBitmap(size, nullptr, 0, &bitmapProperties, &m_pD2DTargetBitmap)))
//__debugbreak();
//
//bitmapProperties.bitmapOptions = D2D1_BITMAP_OPTIONS_CANNOT_DRAW | D2D1_BITMAP_OPTIONS_CPU_READ;
//if (FAILED(m_pD2DDeviceContext->CreateBitmap(size, nullptr, 0, &bitmapProperties, &m_pD2DTargetBitmapRead)))
//__debugbreak();
//
//if (FAILED(m_pD2DDeviceContext->CreateSolidColorBrush(ColorF(ColorF::White), &m_pWhiteBrush)))
//__debugbreak();
//
//HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory5), (IUnknown**)&m_pDWFactory);
//if (FAILED(hr))
//__debugbreak();
//
//bResult = TRUE;
//lb_return:
//return bResult;