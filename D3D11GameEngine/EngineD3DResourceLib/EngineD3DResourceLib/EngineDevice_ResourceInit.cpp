#include "Pre.h"
#include "EngineDevice.h"
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"
#include "EngineInputLayout.h"
#include "EngineVertexShader.h"
#include "EnginePixelShader.h"
#include "EngineRasterizer.h"
#include "EngineDepthStencil.h"

void EngineDevice::ResourceInit()
{
	{
		EngineDirectory Dir;
		Dir.GoChild("EngineShader");
		std::vector<EngineFile> AllShaderFile = Dir.GetAllFile(".fx");

		for (EngineFile& ShaderFile : AllShaderFile)
		{
			std::string FileName = ShaderFile.GetFileName();

			IEngineVertexShader* pVertexShader = Manager->CreateVertexShader(FileName.c_str());
			Manager->SettingVertexShader(pVertexShader, FileName.c_str(), ShaderFile.GetStringPath().c_str());
			
			IEnginePixelShader* pPixelShader = Manager->CreatePixelShader(FileName.c_str());
			Manager->SettingPixelShader(pPixelShader, FileName.c_str(), ShaderFile.GetStringPath().c_str());
		}
	}

	//IA¼³Á¤
	{
		{
			EngineVertexShader* TestVertexShader = (EngineVertexShader*)Manager->FindVertexShader("Test2DShader");

			D3D11_INPUT_ELEMENT_DESC Desc[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};

			IEngineInputLayout* pInputLayout = Manager->CreateInputLayout("Pos");
			Manager->SettingInputLayout(pInputLayout, 1, Desc, TestVertexShader->GetShaderByteCode(), TestVertexShader->GetShaderByteLength());
		}

		{
			EngineVertexShader* TestVertexShader = (EngineVertexShader*)Manager->FindVertexShader("Test3DShader");

			D3D11_INPUT_ELEMENT_DESC Desc[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};

			IEngineInputLayout* pInputLayout = Manager->CreateInputLayout("PosColor");
			Manager->SettingInputLayout(pInputLayout, 2, Desc, TestVertexShader->GetShaderByteCode(), TestVertexShader->GetShaderByteLength());
		}

	}

	//Box2D
	{
		float4 Box2D[] =
		{
			float4(-0.5f, 0.5f),
			float4(0.5f, 0.5f),
			float4(0.5f, -0.5f),
			float4(-0.5f, -0.5f)
		};
		IEngineVertexBuffer* pVertexBuffer = Manager->CreateVertexBuffer("Box2D");
		Manager->SettingVertexBuffer(pVertexBuffer, Box2D, sizeof(float4), sizeof(Box2D));
	}

	{
		UINT Box2D[]
		{
			0,1,2,
			0,2,3
		};
		IEngineIndexBuffer* pIndexBuffer = Manager->CreateIndexBuffer("Box2D");
		Manager->SettingIndexBuffer(pIndexBuffer, Box2D, sizeof(Box2D));
	}

	//Box3D
	{
		VERTEX_POS_COLOR Box3D[] =
		{
			//¾Õ¸é
			//»¡°­
			{ float4(-0.5f, 0.5f, -0.5f, 1.0f), float4(1.0f, 0.0f, 0.0f, 1.0f) },
			{ float4(0.5f, 0.5f, -0.5f, 1.0f),  float4(1.0f, 0.0f, 0.0f, 1.0f) },
			{ float4(0.5f, -0.5f, -0.5f, 1.0f), float4(1.0f, 0.0f, 0.0f, 1.0f) },
			{ float4(-0.5f, -0.5f, -0.5f, 1.0f),float4(1.0f, 0.0f, 0.0f, 1.0f) },

			//µÞ¸é
			//ÆÄ¶û
			{ float4(-0.5f, 0.5f, 0.5f, 1.0f),  float4(0.0f, 0.0f, 1.0f, 1.0f) },
			{ float4(0.5f, 0.5f, 0.5f, 1.0f),   float4(0.0f, 0.0f, 1.0f, 1.0f) },
			{ float4(0.5f, -0.5f, 0.5f, 1.0f),  float4(0.0f, 0.0f, 1.0f, 1.0f) },
			{ float4(-0.5f, -0.5f, 0.5f, 1.0f), float4(0.0f, 0.0f, 1.0f, 1.0f) },

			//¿ÞÂÊ
			//ÃÊ·Ï
			{ float4(-0.5f, 0.5f, -0.5f, 1.0f), float4(0.0f, 1.0f, 0.0f, 1.0f) },
			{ float4(-0.5f, 0.5f, 0.5f, 1.0f),  float4(0.0f, 1.0f, 0.0f, 1.0f) },
			{ float4(-0.5f, -0.5f, 0.5f, 1.0f), float4(0.0f, 1.0f, 0.0f, 1.0f) },
			{ float4(-0.5f, -0.5f, -0.5f, 1.0f),float4(0.0f, 1.0f, 0.0f, 1.0f) },

			//¿À¸¥ÂÊ
			//¸¶Á¨Å¸
			{ float4(0.5f, 0.5f, -0.5f, 1.0f),  float4(1.0f, 0.0f, 1.0f, 1.0f) },
			{ float4(0.5f, 0.5f, 0.5f, 1.0f),   float4(1.0f, 0.0f, 1.0f, 1.0f) },
			{ float4(0.5f, -0.5f, 0.5f, 1.0f),  float4(1.0f, 0.0f, 1.0f, 1.0f) },
			{ float4(0.5f, -0.5f, -0.5f, 1.0f), float4(1.0f, 0.0f, 1.0f, 1.0f) },

			//À­¸é
			//ÇÏ´Ã
			{ float4(-0.5f, 0.5f, -0.5f, 1.0f), float4(0.0f, 1.0f, 1.0f, 1.0f) },
			{ float4(-0.5f, 0.5f, 0.5f, 1.0f),  float4(0.0f, 1.0f, 1.0f, 1.0f) },
			{ float4(0.5f, 0.5f, 0.5f, 1.0f),   float4(0.0f, 1.0f, 1.0f, 1.0f) },
			{ float4(0.5f, 0.5f, -0.5f, 1.0f),  float4(0.0f, 1.0f, 1.0f, 1.0f) },

			//¾Æ·§¸é
			//Èò»ö
			{ float4(-0.5f, -0.5f, -0.5f, 1.0f),float4(1.0f, 1.0f, 1.0f, 1.0f) },
			{ float4(-0.5f, -0.5f, 0.5f, 1.0f), float4(1.0f, 1.0f, 1.0f, 1.0f) },
			{ float4(0.5f, -0.5f, 0.5f, 1.0f),  float4(1.0f, 1.0f, 1.0f, 1.0f) },
			{ float4(0.5f, -0.5f, -0.5f, 1.0f), float4(1.0f, 1.0f, 1.0f, 1.0f) } ,
		};

		IEngineVertexBuffer* pVertexBuffer = Manager->CreateVertexBuffer("Box3D");
		Manager->SettingVertexBuffer(pVertexBuffer, Box3D, sizeof(VERTEX_POS_COLOR), sizeof(Box3D));
	}

	{
		UINT Box3D[]
		{
			//¾Õ¸é
			0,1,2,
			2,3,0,

			//µÞ¸é
			4,5,6,
			6,7,4,

			//¿ÞÂÊ
			8,9,10,
			10,11,8,

			//¿À¸¥ÂÊ
			12,13,14,
			14,15,12,

			//À§ÂÊ
			16,17,18,
			18,19,16,

			//¾Æ·¡ÂÊ
			20,21,22,
			22,23,20
		};

		IEngineIndexBuffer* pIndexBuffer = Manager->CreateIndexBuffer("Box3D");
		Manager->SettingIndexBuffer(pIndexBuffer, Box3D, sizeof(Box3D));
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
		
		IEngineRasterizer* pRasterizer = Manager->CreateRasterizer("Default");
		Manager->SettingRasterizer(pRasterizer, Desc);
	}

	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0 };
		Desc.DepthEnable = true;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_LESS;
		Desc.StencilEnable = false;

		IEngineDepthStencil* pDepthStencil = Manager->CreateDepthStencil("Default");
		Manager->SettingDepthStencil(pDepthStencil, Desc);
	}

}