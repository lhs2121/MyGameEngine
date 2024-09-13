#pragma once
#include "d3d11.h"
#include <ThirdParty/include/DirectXTex.h>

struct Named
{
	EngineString name;
};

struct CanDraw : public Named
{
	virtual void Draw() {};
	void SetContext(ID3D11DeviceContext* _pContext) { pContext = _pContext; }

protected:
	ID3D11DeviceContext* pContext = nullptr;
};
struct VertexBuffer : public Named
{
	ID3D11Buffer* pBuffer = nullptr;
	UINT strides;
	UINT offsets;


	~VertexBuffer()
	{
		pBuffer->Release();
	}
};

struct IndexBuffer : public Named
{
	ID3D11Buffer* pBuffer = nullptr;
	UINT count;
	UINT strides;
	UINT offsets;


	~IndexBuffer()
	{
		pBuffer->Release();
	}
};

struct VertexShader : public Named
{
	ID3DBlob* pBlob = nullptr;
	ID3D11VertexShader* pShader = nullptr;


	~VertexShader()
	{
		pBlob->Release();
		pShader->Release();
	}
};

struct PixelShader : public Named
{
	ID3DBlob* pBlob = nullptr;
	ID3D11PixelShader* pShader = nullptr;


	~PixelShader()
	{
		pBlob->Release();
		pShader->Release();
	}
};

struct InputLayout : public CanDraw
{
	void Draw() override
	{
		pContext->IASetInputLayout(pLayout);
	}
	std::vector<D3D11_INPUT_ELEMENT_DESC> desc;
	ID3D11InputLayout* pLayout = nullptr;


	~InputLayout()
	{
		pLayout->Release();
	}
};

struct Rasterizer : public Named
{
	D3D11_RASTERIZER_DESC desc;
	ID3D11RasterizerState* pState = nullptr;


	~Rasterizer()
	{
		pState->Release();
	}
};

struct DepthStencil : public Named
{
	D3D11_DEPTH_STENCIL_DESC desc;
	ID3D11DepthStencilState* pState = nullptr;


	~DepthStencil()
	{
		pState->Release();
	}
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


	~ConstantBuffer()
	{
		pBuffer->Release();
	}
};

struct Texture : public Named
{
	ID3D11ShaderResourceView* pShaderResourceView = nullptr;
	DirectX::ScratchImage scratchImage;
	DirectX::TexMetadata metaData;


	~Texture()
	{
		pShaderResourceView->Release();
	}
};

struct Sampler : public Named
{
	ID3D11SamplerState* pState = nullptr;


	~Sampler()
	{
		pState->Release();
	}
};

struct Blend : public Named
{
	ID3D11BlendState* pState = nullptr;

	~Blend()
	{
		pState->Release();
	}
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
	Blend* pBlend = nullptr;

	void Draw() override
	{
		pContext->VSSetShader(pVertexShader->pShader, nullptr, 0);
		pContext->PSSetShader(pPixelShader->pShader, nullptr, 0);
		if (pSampler != nullptr)
		{
			pContext->PSSetSamplers(0, 1, &pSampler->pState);
		}
		if (pTexture != nullptr)
		{
			pContext->PSSetShaderResources(0, 1, &pTexture->pShaderResourceView);
		}
		if (pRasterizer != nullptr)
		{
			pContext->RSSetState(pRasterizer->pState);
		}
		if (pBlend != nullptr)
		{
			pContext->OMSetBlendState(pBlend->pState, nullptr, 0xFFFFFFFF);
		}
		if (pDepthStencil != nullptr)
		{
			pContext->OMSetDepthStencilState(pDepthStencil->pState, 0);
		}
		
	}
};