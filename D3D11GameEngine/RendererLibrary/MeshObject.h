#pragma once
#include "ConstantBuffer.h"
#include "Interface.h"

class MeshObject : public IMeshObject
{
public:
	void Draw(ID3D11DeviceContext* pContext);
	void SetSolid() override;
	void SetWireFrame() override;
	UINT m_stride = 16;
	UINT m_offset = 0;
	UINT m_indexCount;
	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11Buffer* m_pIndexBuffer = nullptr;
	ConstantBuffer* m_pTransformBuffer = nullptr;
	ID3D11RasterizerState* m_pRasterizer = nullptr;
	ID3D11DepthStencilState* m_pDepthStencil = nullptr;
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;
	ID3D11InputLayout* m_pInputLayout = nullptr;
	ID3D11SamplerState* m_pSampler = nullptr;
	ID3D11BlendState* m_pBlend = nullptr;
	ID3D11ShaderResourceView* m_pShaderResourceView = nullptr;
};