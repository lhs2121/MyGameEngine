#include "Pre.h"
#include "EngineDevice.h"
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"
#include "EngineInputLayout.h"
#include "EngineVertexShader.h"
#include "EnginePixelShader.h"

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

	{
		float4 Rect[] =
		{
			float4(-0.5f, 0.5f, 0.0f, 1.0f),
			float4(0.5f, 0.5f, 0.0f, 1.0f),
			float4(0.5f, -0.5f, 0.0f, 1.0f),
			float4(-0.5f, -0.5f, 0.0f, 1.0f)
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
}