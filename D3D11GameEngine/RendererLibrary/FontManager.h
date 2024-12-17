#pragma once
#include "IRenderer.h"
#include <map>
#include <string>
#include "dwrite.h"

class CFontManager
{
public:
	void Initialize(ID3D11Device* pDevice,IDXGISurface* pBackBuffer, float pWinWidth, float pWinHeight);
	void FontRender(const wchar_t* str, float posX, float posY, float width, float height);
private:
	float m_pWinWidth;
	float m_pWinHeight;
	std::map<std::wstring, IDWriteTextLayout*> m_mapLayout;
	IDWriteFactory* m_pDwriteFactory = nullptr;
	ID2D1RenderTarget* m_pD2D1RenderTarget = nullptr;
	ID2D1Device2* m_pD2D1Device = nullptr;
	ID2D1DeviceContext2* m_pD2D1DeviceContext = nullptr;
	ID2D1SolidColorBrush* m_pBrush = nullptr;
	IDWriteTextFormat* m_pArial = nullptr;
	IDWriteTextLayout* m_pLayout = nullptr;
};