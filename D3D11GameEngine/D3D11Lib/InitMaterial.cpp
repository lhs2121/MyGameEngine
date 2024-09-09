#include "Pre.h"
#include "Device.h"
#include "D3D11API.h"

void Device::InitMaterial(IResManager* pManager)
{
	{
		EngineDirectory Dir;

		Dir.GoChild("EngineShader");
		std::vector<EngineFile> AllShaderFile = Dir.GetAllFileExt(".fx");

		for (EngineFile& ShaderFile : AllShaderFile)
		{
			EngineString FileName = ShaderFile.GetFileName();
			EngineString FilePath = ShaderFile.GetPath();

			IVertexShader* pVS = (IVertexShader*)pManager->CreateResource( ResType::VS, FileName);
			pVS->Setting( FileName, FilePath);

			IPixelShader* pPS = (IPixelShader*)pManager->CreateResource(ResType::PS, FileName);
			pPS->Setting(FileName, FilePath);
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

		IRasterizer* pRasterizer = (IRasterizer*)pManager->CreateResource(ResType::RS, "Default");
		pRasterizer->Setting( Desc);
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

		IRasterizer* pRasterizer = (IRasterizer*)pManager->CreateResource(ResType::RS, "WireFrame");
		pRasterizer->Setting( Desc);
	}

	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0 };
		Desc.DepthEnable = false;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_LESS;
		Desc.StencilEnable = false;

		IDepthStencil* pDepthStencil = (IDepthStencil*)pManager->CreateResource(ResType::DS, "Default");
		pDepthStencil->Setting( Desc);
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

		ISampler* NewSampler = (ISampler*)pManager->CreateResource(ResType::Sampler, "Point");
		NewSampler->Setting( &Desc);
	}

	{
		EngineDirectory Dir;
		Dir.GoBase();
		Dir.GoChild("Assets");
		std::vector<EngineFile> Files = Dir.GetAllFileExt(".png");

		ITexture* NewTexture = (ITexture*)pManager->CreateResource( ResType::Texture, "Default");
		NewTexture->Setting( Files[0]);
	}

	{
		IMaterial* NewMat = (IMaterial*)pManager->CreateResource( ResType::Material, "Sprite2D");
		NewMat->SetShader("Sprite2D");
		NewMat->SetRS("Default");
		NewMat->SetDS("Default");
		NewMat->SetSampler("Point");
		NewMat->SetTexture("Default");

	}

	{
		IMaterial* NewMat = (IMaterial*)pManager->CreateResource( ResType::Material, "DebugLine");
		NewMat->SetShader("DebugLine");
		NewMat->SetRS("WireFrame");
		NewMat->SetDS("Default");
		NewMat->SetSampler("Point");
		NewMat->SetTexture("Default");

	}
}
