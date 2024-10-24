#pragma once
#include "IRenderer.h"

class CRenderer;
class CMaterial : public IMaterial
{
public:
	void SetTexture(const WCHAR* wszTexName) override;
	CMaterial* Copy();
	void Draw(ID3D11DeviceContext* pDeviceContext);

	CRenderer* m_pRenderer = nullptr;
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3DBlob* m_pCompiledVertexShader = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;

	ID3D11ShaderResourceView* m_pShaderResourceView = nullptr;
};