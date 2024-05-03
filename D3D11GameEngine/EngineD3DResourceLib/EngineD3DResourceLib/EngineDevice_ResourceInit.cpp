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

			IEngineVertexShader* pVertexShader = m_pManager->CreateVertexShader(FileName.c_str());
			m_pManager->SettingVertexShader(pVertexShader, FileName.c_str(), ShaderFile.GetStringPath().c_str());
			
			IEnginePixelShader* pPixelShader = m_pManager->CreatePixelShader(FileName.c_str());
			m_pManager->SettingPixelShader(pPixelShader, FileName.c_str(), ShaderFile.GetStringPath().c_str());
		}
	}

	//IA¼³Á¤
	{
		EngineVertexShader* TestVertexShader = (EngineVertexShader*)m_pManager->FindVertexShader("TestShader");
		{
			D3D11_INPUT_ELEMENT_DESC Desc[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};

			IEngineInputLayout* pInputLayout = m_pManager->CreateInputLayout("POSCOLOR");
			m_pManager->SettingInputLayout(pInputLayout, 2, Desc, TestVertexShader->GetShaderByteCode(), TestVertexShader->GetShaderByteLength());
		}
	}

	////Box2D
	//{
	//	float4 Rect[] =
	//	{
	//		float4(-0.5f, 0.5f, -0.5f, 0.5f),
	//		float4(0.5f, 0.5f, -0.5f, 0.5f),
	//		float4(0.5f, -0.5f, -0.5f, 0.5f),
	//		float4(-0.5f, -0.5f, -0.5f, 0.5f)
	//	};
	//	EngineVertexBuffer* NewVertexBuffer = EngineVertexBuffer::RegisterResource("Rect");
	//	NewVertexBuffer->CreateResource(Rect, sizeof(Rect));
	//}

	//{
	//	UINT Rect[]
	//	{
	//		0,1,2,
	//		0,2,3
	//	};
	//	EngineIndexBuffer* NewIndexBuffer = EngineIndexBuffer::RegisterResource("Rect");
	//	NewIndexBuffer->CreateResource(Rect, sizeof(Rect));
	//}

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

		IEngineVertexBuffer* pVertexBuffer = m_pManager->CreateVertexBuffer("Box3D");
		m_pManager->SettingVertexBuffer(pVertexBuffer, Box3D,sizeof(Box3D));
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

		IEngineIndexBuffer* pIndexBuffer = m_pManager->CreateIndexBuffer("Box3D");
		m_pManager->SettingIndexBuffer(pIndexBuffer, Box3D, sizeof(Box3D));
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
		
		IEngineRasterizer* pRasterizer = m_pManager->CreateRasterizer("Default");
		m_pManager->SettingRasterizer(pRasterizer, Desc);
	}

	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0 };
		Desc.DepthEnable = true;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_LESS;
		Desc.StencilEnable = false;

		IEngineDepthStencil* pDepthStencil = m_pManager->CreateDepthStencil("Default");
		m_pManager->SettingDepthStencil(pDepthStencil, Desc);
	}

}