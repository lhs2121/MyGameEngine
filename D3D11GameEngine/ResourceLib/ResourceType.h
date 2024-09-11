#pragma once
#include "d3d11.h"
#include <ThirdParty/include/DirectXTex.h>

struct Named
{
	const char* name;
};

struct CanDraw : public Named
{
	void SetContext(ID3D11DeviceContext* _pContext) { pContext = _pContext; }
	virtual void Draw() {};

protected:
	ID3D11DeviceContext* pContext = nullptr;
};
struct VertexBuffer : public Named
{
	ID3D11Buffer* pBuffer = nullptr;
	UINT strides;
	UINT offsets;
};

struct IndexBuffer : public Named
{
	ID3D11Buffer* pBuffer = nullptr;
	UINT count;
	UINT strides;
	UINT offsets;
};

struct VertexShader : public Named
{
	ID3DBlob* pBlob = nullptr;
	ID3D11VertexShader* pShader = nullptr;
};

struct PixelShader : public Named
{
	ID3DBlob* pBlob = nullptr;
	ID3D11PixelShader* pShader = nullptr;
};

struct InputLayout : public CanDraw
{
	void Draw() override
	{
		pContext->IASetInputLayout(pLayout);
	}
	std::vector<D3D11_INPUT_ELEMENT_DESC> desc;
	ID3D11InputLayout* pLayout = nullptr;
};

struct Rasterizer : public Named
{
	D3D11_RASTERIZER_DESC desc;
	ID3D11RasterizerState* pState = nullptr;
};

struct DepthStencil : public Named
{
	D3D11_DEPTH_STENCIL_DESC desc;
	ID3D11DepthStencilState* pState = nullptr;
};

enum class ShaderType
{
	VS,
	PS
};

struct ConstantBuffer : public CanDraw
{
	int dataSize;
	void* pData = nullptr;
	ID3D11Buffer* pBuffer = nullptr;
	ShaderType Type;
	void SetContext(ID3D11DeviceContext* _pContext) { pContext = _pContext; }
	void Draw()
	{
		D3D11_MAPPED_SUBRESOURCE MappedRes;

		pContext->Map(pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedRes);
		memcpy_s(MappedRes.pData, dataSize, pData, dataSize);

		pContext->Unmap(pBuffer, 0);

		switch (Type)
		{
		case ShaderType::VS:
			pContext->VSSetConstantBuffers(0, 1, &pBuffer);

			break;
		case ShaderType::PS:

			pContext->PSSetConstantBuffers(0, 1, &pBuffer);
			break;
		}
	}
};

struct Texture : public Named
{
	ID3D11ShaderResourceView* pShaderResourceView = nullptr;
	DirectX::ScratchImage scratchImage;
	DirectX::TexMetadata metaData;
};

struct Sampler : public Named
{
	ID3D11SamplerState* pState = nullptr;
};

struct Mesh : public CanDraw
{
	VertexBuffer* pVertexBuffer = nullptr;
	IndexBuffer* pIndexBuffer = nullptr;

	void Draw() override
	{
		pContext->IASetVertexBuffers(0, 1, &pVertexBuffer->pBuffer, &pVertexBuffer->strides, &pVertexBuffer->offsets);
		pContext->IASetIndexBuffer(pIndexBuffer->pBuffer, DXGI_FORMAT_R32_UINT, pIndexBuffer->offsets);
	}
};

struct Material : public CanDraw
{
	VertexShader* pVertexShader = nullptr;
	PixelShader* pPixelShader = nullptr;
	Rasterizer* pRasterizer = nullptr;
	DepthStencil* pDepthStencil = nullptr;
	Sampler* pSampler = nullptr;
	Texture* pTexture = nullptr;

	void Draw() override
	{
		pContext->VSSetShader(pVertexShader->pShader, nullptr, 0);
		pContext->PSSetShader(pPixelShader->pShader, nullptr, 0);
		pContext->PSSetSamplers(0,1,&pSampler->pState);
		pContext->PSSetShaderResources(0,1,&pTexture->pShaderResourceView);
		pContext->RSSetState(pRasterizer->pState);
		pContext->OMSetDepthStencilState(pDepthStencil->pState,0);
	}
};