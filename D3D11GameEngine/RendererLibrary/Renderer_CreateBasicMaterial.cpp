#include "pch.h"
#include "Renderer.h"

void CRenderer::CreateBasicMaterial()
{
	D3D11_RASTERIZER_DESC Desc_Solid = {};
	Desc_Solid.FillMode = D3D11_FILL_SOLID;
	Desc_Solid.CullMode = D3D11_CULL_BACK;
	Desc_Solid.FrontCounterClockwise = false; //시계방향
	Desc_Solid.DepthBias = 0;
	Desc_Solid.DepthBiasClamp = 0;
	Desc_Solid.SlopeScaledDepthBias = 0;
	Desc_Solid.DepthClipEnable = true;
	Desc_Solid.ScissorEnable = false;
	Desc_Solid.MultisampleEnable = true;
	Desc_Solid.AntialiasedLineEnable = false;

	if (S_OK != m_pDevice->CreateRasterizerState(&Desc_Solid, &m_pRasterizerState_Solid))
		__debugbreak();

	D3D11_RASTERIZER_DESC Desc_WireFrame = {};
	Desc_WireFrame.FillMode = D3D11_FILL_WIREFRAME;
	Desc_WireFrame.CullMode = D3D11_CULL_NONE;
	Desc_WireFrame.FrontCounterClockwise = false;
	Desc_WireFrame.DepthBias = 0;
	Desc_WireFrame.DepthBiasClamp = 0;
	Desc_WireFrame.SlopeScaledDepthBias = 0;
	Desc_WireFrame.DepthClipEnable = true;
	Desc_WireFrame.ScissorEnable = false;
	Desc_WireFrame.MultisampleEnable = false;
	Desc_WireFrame.AntialiasedLineEnable = false;

	if (S_OK != m_pDevice->CreateRasterizerState(&Desc_WireFrame, &m_pRasterizerState_WireFrame))
		__debugbreak();

	D3D11_SAMPLER_DESC Desc_Point = {};
	Desc_Point.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	Desc_Point.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc_Point.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc_Point.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc_Point.MipLODBias = 0.0f;
	Desc_Point.MaxAnisotropy = 1;
	Desc_Point.ComparisonFunc = D3D11_COMPARISON_NEVER;
	Desc_Point.BorderColor[0] = 1.0f;
	Desc_Point.BorderColor[1] = 1.0f;
	Desc_Point.BorderColor[2] = 1.0f;
	Desc_Point.BorderColor[3] = 1.0f;
	Desc_Point.MinLOD = 0;
	Desc_Point.MaxLOD = D3D11_FLOAT32_MAX;

	if (S_OK != m_pDevice->CreateSamplerState(&Desc_Point, &m_pSamplerState_Point))
		__debugbreak();

	D3D11_BLEND_DESC Desc_Alpha_On = { 0 };
	Desc_Alpha_On.AlphaToCoverageEnable = true;
	Desc_Alpha_On.IndependentBlendEnable = false;
	Desc_Alpha_On.RenderTarget[0].BlendEnable = true;
	Desc_Alpha_On.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	Desc_Alpha_On.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	Desc_Alpha_On.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	Desc_Alpha_On.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	Desc_Alpha_On.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	Desc_Alpha_On.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	Desc_Alpha_On.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	if (S_OK != m_pDevice->CreateBlendState(&Desc_Alpha_On, &m_pBlendState_Alhpa_On))
		__debugbreak();

	D3D11_DEPTH_STENCIL_DESC Desc_Depth_On = { 0 };
	Desc_Depth_On.DepthEnable = true;
	Desc_Depth_On.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	Desc_Depth_On.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	Desc_Depth_On.StencilEnable = false;

	if (S_OK != m_pDevice->CreateDepthStencilState(&Desc_Depth_On, &m_pDepthStencilState_Depth_On))
		__debugbreak();

	m_pBasicColor = (CMaterial*)CreateMaterial("BasicColor", L"BasicColorShader.hlsl", nullptr);
	m_pBasicSprite2D = (CMaterial*)CreateMaterial("BasicSprite2D", L"BasicSprite2DShader.hlsl", L"asdf.jpg");
}