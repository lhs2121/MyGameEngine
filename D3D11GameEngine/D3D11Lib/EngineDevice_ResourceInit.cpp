#include "Pre.h"
#include "EngineDevice.h"
#include "EngineVertexFormat.h"
#include "D3D11API.h"

void EngineDevice::ResourceInit(IEngineD3DManager* pManager)
{
	{
		EngineDirectory Dir;

		Dir.GoChild("EngineShader");
		std::vector<EngineFile> AllShaderFile = Dir.GetAllFileExt(".fx");

		for (EngineFile& ShaderFile : AllShaderFile)
		{
			EngineString FileName = ShaderFile.GetFileName();
			EngineString FilePath = ShaderFile.GetPath();

			IEngineVertexShader* pVS = (IEngineVertexShader*)pManager->CreateResource(ResType::VS, FileName);
			pVS->Setting(FileName, FilePath);

			IEnginePixelShader* pPS = (IEnginePixelShader*)pManager->CreateResource(ResType::PS, FileName);
			pPS->Setting(FileName, FilePath);
		}
	}

	//Box2D
	{
		Vertex Box2D[] =
		{
			{float4(-0.5f, 0.5f), float2(0,0)},
			{float4( 0.5f, 0.5f), float2(1,0)},
			{float4( 0.5f,-0.5f), float2(1,1)},
			{float4(-0.5f,-0.5f), float2(0,1)}
		};
		IEngineVertexBuffer* pVertexBuffer = (IEngineVertexBuffer*)pManager->CreateResource(ResType::VB, "Box2D");
		pVertexBuffer->Setting(Box2D, sizeof(Vertex), sizeof(Box2D), 0);
	}

	{
		UINT Box2D[]
		{
			0,1,2,
			0,2,3
		};
		IEngineIndexBuffer* pIndexBuffer = (IEngineIndexBuffer*)pManager->CreateResource(ResType::IB, "Box2D");
		pIndexBuffer->Setting(Box2D, sizeof(Box2D));
	}

	//Box3D
	{
		Vertex Box3D[] =
		{
			// Front                      
			{ float4(-0.5f, 0.5f,-0.5f, 1.0f), float2(0,0) },
			{ float4( 0.5f, 0.5f,-0.5f, 1.0f), float2(1,0) },
			{ float4( 0.5f,-0.5f,-0.5f, 1.0f), float2(1,1) },
			{ float4(-0.5f,-0.5f,-0.5f, 1.0f), float2(0,1) },

			// Back                 
			{ float4(-0.5f, 0.5f, 0.5f, 1.0f), float2(0,0) },
			{ float4( 0.5f, 0.5f, 0.5f, 1.0f), float2(1,0) },
			{ float4( 0.5f,-0.5f, 0.5f, 1.0f), float2(1,1) },
			{ float4(-0.5f,-0.5f, 0.5f, 1.0f), float2(0,1) },

			// Left                           
			{ float4(-0.5f, 0.5f,-0.5f, 1.0f), float2(0,0) },
			{ float4(-0.5f, 0.5f, 0.5f, 1.0f), float2(1,0) },
			{ float4(-0.5f,-0.5f, 0.5f, 1.0f), float2(1,1) },
			{ float4(-0.5f,-0.5f,-0.5f, 1.0f), float2(0,1) },

			// Right                          
			{ float4(0.5f, 0.5f,-0.5f, 1.0f),  float2(0,0) },
			{ float4(0.5f, 0.5f, 0.5f, 1.0f),  float2(1,0) },
			{ float4(0.5f,-0.5f, 0.5f, 1.0f),  float2(1,1) },
			{ float4(0.5f,-0.5f,-0.5f, 1.0f),  float2(0,1) },

			// Top                            
			{ float4(-0.5f, 0.5f,-0.5f, 1.0f), float2(0,0) },
			{ float4(-0.5f, 0.5f, 0.5f, 1.0f), float2(1,0) },
			{ float4( 0.5f, 0.5f, 0.5f, 1.0f), float2(1,1) },
			{ float4( 0.5f, 0.5f,-0.5f, 1.0f), float2(0,1) },

			// Bottom                         
			{ float4(-0.5f,-0.5f,-0.5f, 1.0f), float2(0,0) },
			{ float4(-0.5f,-0.5f, 0.5f, 1.0f), float2(1,0) },
			{ float4( 0.5f,-0.5f, 0.5f, 1.0f), float2(1,1) },
			{ float4( 0.5f,-0.5f,-0.5f, 1.0f), float2(0,1) }
		};

		IEngineVertexBuffer* pVertexBuffer = (IEngineVertexBuffer*)pManager->CreateResource(ResType::VB, "Box3D");
		pVertexBuffer->Setting(Box3D, sizeof(Vertex), sizeof(Box3D), 1);
	}

	{
		UINT Box3D[]
		{
			// Front
			0,1,2,
			2,3,0,

			// Back
			4,5,6,
			6,7,4,

			// Left
			8,9,10,
			10,11,8,

			// Right
			12,13,14,
			14,15,12,

			// Top
			16,17,18,
			18,19,16,

			// Bottom
			20,21,22,
			22,23,20
		};

		IEngineIndexBuffer* pIndexBuffer = (IEngineIndexBuffer*)pManager->CreateResource(ResType::IB, "Box3D");
		pIndexBuffer->Setting(Box3D, sizeof(Box3D));
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

		IEngineRasterizer* pRasterizer = (IEngineRasterizer*)pManager->CreateResource(ResType::RS, "Default");
		pRasterizer->Setting(Desc);
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

		IEngineRasterizer* pRasterizer = (IEngineRasterizer*)pManager->CreateResource(ResType::RS, "Wire");
		pRasterizer->Setting(Desc);
	}

	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0 };
		Desc.DepthEnable = true;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_LESS;
		Desc.StencilEnable = false;

		IEngineDepthStencil* pDepthStencil = (IEngineDepthStencil*)pManager->CreateResource(ResType::DS, "Default");
		pDepthStencil->Setting(Desc);
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

		IEngineSampler* NewSampler = (IEngineSampler*)pManager->CreateResource(ResType::Sampler, "Point");
		NewSampler->Setting(&Desc);
	}

	{
		EngineDirectory Dir;
		Dir.GoBase();
		Dir.GoChild("Assets");
		std::vector<EngineFile> Files = Dir.GetAllFileExt(".png");

		IEngineTexture* NewTexture = (IEngineTexture*)pManager->CreateResource(ResType::Texture, "Default");
		NewTexture->Setting(Files[0]);
	}

	{
		IMesh* NewMesh = (IMesh*)pManager->CreateResource(ResType::Mesh, "Box2D");
		NewMesh->Setting("Box2D", "Box2D");
	}

	{
		IMaterial* NewMat = (IMaterial*)pManager->CreateResource(ResType::Material, "Sprite2D");
		NewMat->SetShader("Sprite2D");
		NewMat->SetRS("Default");
		NewMat->SetDS("Default");
		NewMat->SetSampler("Point");
		NewMat->SetTexture("Default");

	}

	{
		IMaterial* NewMat = (IMaterial*)pManager->CreateResource(ResType::Material, "DebugLine");
		NewMat->SetShader("DebugLine");
		NewMat->SetRS("Wire");
		NewMat->SetDS("Default");
		NewMat->SetSampler("Point");
		NewMat->SetTexture("Default");

	}

}