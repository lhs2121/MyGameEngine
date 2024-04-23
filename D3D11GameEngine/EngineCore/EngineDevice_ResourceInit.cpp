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

			EngineVertexShader* NewVertexShader = EngineVertexShader::RegisterResource(FileName);
			NewVertexShader->CreateResource(FileName, ShaderFile.GetStringPath());

			EnginePixelShader* NewPixelShader = EnginePixelShader::RegisterResource(FileName);
			NewPixelShader->CreateResource(FileName, ShaderFile.GetStringPath());
		}
	}

	//IA¼³Á¤
	{
		EngineVertexShader* TestVertexShader = EngineVertexShader::Find("TestShader");
		{
			D3D11_INPUT_ELEMENT_DESC Desc[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};

			EngineInputLayout* NewInputLayout = EngineInputLayout::RegisterResource("POS_COLOR");
			NewInputLayout->SetDesc(2, Desc);
			NewInputLayout->CreateResource(TestVertexShader->GetShaderByteCode(), TestVertexShader->GetShaderByteLength());
		}
	}

	//Box2D
	{
		float4 Rect[] =
		{
			float4(-0.5f, 0.5f, -0.5f, 0.5f),
			float4(0.5f, 0.5f, -0.5f, 0.5f),
			float4(0.5f, -0.5f, -0.5f, 0.5f),
			float4(-0.5f, -0.5f, -0.5f, 0.5f)
		};
		EngineVertexBuffer* NewVertexBuffer = EngineVertexBuffer::RegisterResource("Rect");
		NewVertexBuffer->CreateResource(Rect, sizeof(Rect));
	}

	{
		UINT Rect[]
		{
			0,1,2,
			0,2,3
		};
		EngineIndexBuffer* NewIndexBuffer = EngineIndexBuffer::RegisterResource("Rect");
		NewIndexBuffer->CreateResource(Rect, sizeof(Rect));
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
		EngineVertexBuffer* NewVertexBuffer = EngineVertexBuffer::RegisterResource("Box3D");
		NewVertexBuffer->CreateResource(Box3D, sizeof(Box3D));
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

		EngineIndexBuffer* NewIndexBuffer = EngineIndexBuffer::RegisterResource("Box3D");
		NewIndexBuffer->CreateResource(Box3D, sizeof(Box3D));
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

		EngineRasterizer* NewRasterizer = EngineRasterizer::RegisterResource("Default");
		NewRasterizer->CreateResource(Desc);
	}

	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0 };
		Desc.DepthEnable = true;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_LESS;
		Desc.StencilEnable = false;

		EngineDepthStencil* NewDeathStencil = EngineDepthStencil::RegisterResource("Default");
		NewDeathStencil->CreateResource(Desc);
	}

}