#pragma once
#include "IRenderer.h"

class CFontManager : public IFontManager
{
public:
	void Initialize(ID3D11Device* pDevice,IDXGISurface* pBackBuffer) override;

private:
	ID2D1RenderTarget* m_pD2D1RenderTarget = nullptr;
	ID2D1Device2* m_pD2D1Device = nullptr;
	ID2D1DeviceContext2* m_pD2D1DeviceContext = nullptr;
	ID2D1SolidColorBrush* m_pBrush = nullptr;
	IDWriteTextFormat* m_pArial = nullptr;
};