#include "Pre.h"
#include "Device.h"
#include "ResourceAPI.h"
#include "ResourceContainer.h"

void Device::InitMaterial()
{
	{
		EngineDirectory dir;

		dir.GoChild("EngineShader");
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

		Resource::CreateDepthStencil("Default", Desc);
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
		Material* newMaterial = Resource::CreateMaterial("Sprite2D");
		newMaterial->pVertexShader = ResourceContainer<VertexShader>::Find("Sprite2D");
		newMaterial->pPixelShader = ResourceContainer<PixelShader>::Find("Sprite2D");
		newMaterial->pRasterizer = ResourceContainer<Rasterizer>::Find("Default");
		newMaterial->pDepthStencil = ResourceContainer<DepthStencil>::Find("Default");
		newMaterial->pSampler = ResourceContainer<Sampler>::Find("Point");
	}
}
