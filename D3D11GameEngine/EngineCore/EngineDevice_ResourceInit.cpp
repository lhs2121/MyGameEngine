#include "Pre.h"
#include "EngineDevice.h"
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"
#include "EngineInputLayout.h"
#include "EngineVertexShader.h"
#include "EnginePixelShader.h"
#include "EngineRasterizer.h"

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

			{
				D3D11_INPUT_ELEMENT_DESC Desc = { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
				EngineInputLayout* NewInputLayout = EngineInputLayout::RegisterResource("POSITION");
				NewInputLayout->SetDesc(Desc);
				NewInputLayout->CreateResource(NewVertexShader->GetShaderByteCode(), NewVertexShader->GetShaderByteLength());
			}
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
		float4 Box3D[] =
		{
			//¾Õ¸é
			float4(-0.5f, 0.5f, -0.5f),
			float4(0.5f, 0.5f, -0.5f),
			float4(0.5f, -0.5f, -0.5f),
			float4(-0.5f, -0.5f, -0.5f),

			//µÞ¸é
			float4(-0.5f, 0.5f, 0.5f),
			float4(0.5f, 0.5f, 0.5f),
			float4(0.5f, -0.5f, 0.5f),
			float4(-0.5f, -0.5f, 0.5f),


	        //¿ÞÂÊ
	        float4(-0.5f, 0.5f, -0.5f),
	        float4(-0.5f, 0.5f, 0.5f),
	        float4(-0.5f, -0.5f, 0.5f),
	        float4(-0.5f, -0.5f, -0.5f),

			//¿À¸¥ÂÊ
	        float4(0.5f, 0.5f, -0.5f),
	        float4(0.5f, 0.5f, 0.5f),
	        float4(0.5f, -0.5f, 0.5f),
	        float4(0.5f, -0.5f, -0.5f),
	        
			//À­¸é
			float4(-0.5f, 0.5f, -0.5f),
			float4(-0.5f, 0.5f, 0.5f),
			float4(0.5f, 0.5f, 0.5f),
			float4(0.5f, 0.5f, -0.5f),

			//¾Æ·§¸é
			float4(-0.5f, -0.5f, -0.5f),
			float4(-0.5f, -0.5f, 0.5f),
			float4(0.5f, -0.5f, 0.5f),
			float4(0.5f, -0.5f, -0.5f)
		};
		EngineVertexBuffer* NewVertexBuffer = EngineVertexBuffer::RegisterResource("Box3D");
		NewVertexBuffer->CreateResource(Box3D, sizeof(Box3D));
	}

	{
		UINT Box3D[]
		{
			//¾Õ¸é
			0,1,2,
			2,3,4,

			//µÞ¸é
			4,5,6,
			4,6,7,

			//À§ÂÊ¸é
			8,9,10,
			8,10,11,

			//¾Æ·¡ÂÊ¸é
			12,13,14,
			12,14,15,

			//¿ÞÂÊ¸é
			16,17,18,
			16,18,19,

			//¿À¸¥ÂÊ¸é
			20,21,22,
			20,22,23
		};

		EngineIndexBuffer* NewIndexBuffer = EngineIndexBuffer::RegisterResource("Box3D");
		NewIndexBuffer->CreateResource(Box3D, sizeof(Box3D));
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

		EngineRasterizer* NewRasterizer = EngineRasterizer::RegisterResource("Default");
		NewRasterizer->CreateResource(Desc);
	}

	


}