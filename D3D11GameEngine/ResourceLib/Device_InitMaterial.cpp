#include "Pre.h"
#include "Device.h"
#include "ResourceAPI.h"
#include "ResMap.h"

void Device::InitMaterial()
{
	{
		EngineDirectory dir;
		dir.GoChild("Assets");
		dir.GoChild("Shaders");
		std::vector<EngineFile> allShaderFile = dir.GetAllFileExt(".fx");

		for (EngineFile& shaderFile : allShaderFile)
		{
			EngineString path = shaderFile.GetPath();
			EngineString name = shaderFile.GetFileName();

			Resource::CreateVertexShader(name.c_str(), path.c_str());
			Resource::CreatePixelShader(name.c_str(), path.c_str());
		}
	}

	{
		D3D11_RASTERIZER_DESC Desc;

		Desc.FillMode = D3D11_FILL_SOLID;
		Desc.CullMode = D3D11_CULL_NONE;
		Desc.FrontCounterClockwise = false;
		Desc.DepthBias = 0;
		Desc.DepthBiasClamp = 0;
		Desc.SlopeScaledDepthBias = 0;
		Desc.DepthClipEnable = false;
		Desc.ScissorEnable = false;
		Desc.MultisampleEnable = false;
		Desc.AntialiasedLineEnable = false;

		Resource::CreateRasterizer("Default",Desc);
	}

	{
		D3D11_RASTERIZER_DESC Desc;

		Desc.FillMode = D3D11_FILL_WIREFRAME;
		Desc.CullMode = D3D11_CULL_NONE;
		Desc.FrontCounterClockwise = false;
		Desc.DepthBias = 0;
		Desc.DepthBiasClamp = 0;
		Desc.SlopeScaledDepthBias = 0;
		Desc.DepthClipEnable = false;
		Desc.ScissorEnable = false;
		Desc.MultisampleEnable = false;
		Desc.AntialiasedLineEnable = false;

		Resource::CreateRasterizer("WireFrame", Desc);
	}

	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0 };
		Desc.DepthEnable = true;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_LESS;
		Desc.StencilEnable = false;

		Resource::CreateDepthStencil("DepthOn", Desc);
	}

	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0 };
		Desc.DepthEnable = false;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_LESS;
		Desc.StencilEnable = false;

		Resource::CreateDepthStencil("DepthOff", Desc);
	}

	{
		D3D11_SAMPLER_DESC Desc = {};
		Desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		Desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		Desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		Desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		Desc.MipLODBias = 0.0f;
		Desc.MaxAnisotropy = 1;
		Desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		Desc.BorderColor[0] = 1.0f;
		Desc.BorderColor[1] = 1.0f;
		Desc.BorderColor[2] = 1.0f;
		Desc.BorderColor[3] = 1.0f;
		Desc.MinLOD = 0;
		Desc.MaxLOD = D3D11_FLOAT32_MAX;

		Resource::CreateSampler("Point", Desc);
	}

	{
		D3D11_BLEND_DESC desc = { 0 };
		{
			desc.AlphaToCoverageEnable = false;
			desc.IndependentBlendEnable = false;
			desc.RenderTarget[0].BlendEnable = true;
			desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		}
		Resource::CreateBlend("Default", desc);
	}
	{
		Material* newMaterial = Resource::CreateMaterial("Sprite2D");
		newMaterial->pVertexShader = ResMap<VertexShader>::Find("Sprite2D");
		newMaterial->pPixelShader = ResMap<PixelShader>::Find("Sprite2D");
		newMaterial->pRasterizer = ResMap<Rasterizer>::Find("Default");
		newMaterial->pDepthStencil = ResMap<DepthStencil>::Find("DepthOn");
		newMaterial->pBlend = ResMap<Blend>::Find("Default");
		newMaterial->pSampler = ResMap<Sampler>::Find("Point");
	}

	{
		Material* newMaterial = Resource::CreateMaterial("WireFrame");
		newMaterial->pVertexShader = ResMap<VertexShader>::Find("DebugLine");
		newMaterial->pPixelShader = ResMap<PixelShader>::Find("DebugLine");
		newMaterial->pRasterizer = ResMap<Rasterizer>::Find("WireFrame");
		newMaterial->pDepthStencil = ResMap<DepthStencil>::Find("DepthOff");
		newMaterial->pSampler = ResMap<Sampler>::Find("Point");
	}
}
