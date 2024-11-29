#pragma once
#include "IRenderer.h"

class CFontManager : public IFontManager
{
public:
	void Initialize(ID3D11Device* pDevice) override;
};