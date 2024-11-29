#include "pch.h"
#include "FontManager.h"
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")

void CFontManager::Initialize(ID3D11Device* pDevice)
{
	ID2D1Device2* m_pD2D1Device = nullptr;
	D2D1_FACTORY_OPTIONS d2dFactoryOptions = {};
	ID2D1Factory3* pD2DFactory = nullptr;

	if (S_OK != D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory3), &d2dFactoryOptions, (void**)&pD2DFactory))
		__debugbreak();

	IDXGIDevice* pDXGIDevice = nullptr;
	if (S_OK != pDevice->QueryInterface(IID_PPV_ARGS(&pDXGIDevice)))
		__debugbreak();

	if(S_OK != pD2DFactory->CreateDevice(pDXGIDevice, &m_pD2D1Device))
		__debugbreak();
	


}