#pragma once
#include "IRenderer.h"

class CFontManager : public IFontManager
{
public:
	void Initialize(ID3D11Device* pDevice) override;

private:
	ID2D1Device2* m_pD2D1Device = nullptr;
	ID2D1DeviceContext2* m_pD2D1DeviceContext = nullptr;
};