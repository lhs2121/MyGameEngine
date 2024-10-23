#include "pch.h"
#include "Renderer.h"

void CRenderer::CreateBasicMaterial()
{
	D3D11_RASTERIZER_DESC solid = {};
	solid.FillMode = D3D11_FILL_SOLID;
	solid.CullMode = D3D11_CULL_BACK;
	solid.FrontCounterClockwise = false; //시계방향
	solid.DepthBias = 0;
	solid.DepthBiasClamp = 0;
	solid.SlopeScaledDepthBias = 0;
	solid.DepthClipEnable = true;
	solid.ScissorEnable = false;
	solid.MultisampleEnable = true;
	solid.AntialiasedLineEnable = false;
	D3D11_RASTERIZER_DESC wireFrame = {};
	wireFrame.FillMode = D3D11_FILL_WIREFRAME;
	wireFrame.CullMode = D3D11_CULL_NONE;
	wireFrame.FrontCounterClockwise = false;
	wireFrame.DepthBias = 0;
	wireFrame.DepthBiasClamp = 0;
	wireFrame.SlopeScaledDepthBias = 0;
	wireFrame.DepthClipEnable = true;
	wireFrame.ScissorEnable = false;
	wireFrame.MultisampleEnable = false;
	wireFrame.AntialiasedLineEnable = false;
	D3D11_SAMPLER_DESC point = {};
	point.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	point.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	point.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	point.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	point.MipLODBias = 0.0f;
	point.MaxAnisotropy = 1;
	point.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	point.BorderColor[0] = 1.0f;
	point.BorderColor[1] = 1.0f;
	point.BorderColor[2] = 1.0f;
	point.BorderColor[3] = 1.0f;
	point.MinLOD = 0;
	point.MaxLOD = D3D11_FLOAT32_MAX;
	D3D11_BLEND_DESC alphaOn = { 0 };
	alphaOn.AlphaToCoverageEnable = true;
	alphaOn.IndependentBlendEnable = false;
	alphaOn.RenderTarget[0].BlendEnable = true;
	alphaOn.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	alphaOn.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	alphaOn.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	alphaOn.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	alphaOn.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	alphaOn.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	alphaOn.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	D3D11_DEPTH_STENCIL_DESC depthOn = { 0 };
	depthOn.DepthEnable = true;
	depthOn.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthOn.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthOn.StencilEnable = false;

	LoadTexture(L"Texture\\asdf.jpg");
	m_pBasicColor = CreateMaterial("BasicColor", L"Shaders\\BasicColorShader.hlsl", nullptr, &wireFrame, &point, nullptr, &depthOn);
	m_pBasicSprite2D = CreateMaterial("BasicSprite2D", L"Shaders\\BasicSprite2DShader.hlsl", L"asdf.jpg", &solid, &point, &alphaOn, &depthOn);
}