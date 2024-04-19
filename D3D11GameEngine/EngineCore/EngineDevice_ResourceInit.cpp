#include "Pre.h"
#include "EngineDevice.h"
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"
#include "EngineInputLayout.h"
#include "EngineVertexShader.h"
#include "EnginePixelShader.h"

void EngineDevice::ResourceInit()
{
	EngineDirectory Dir;
	Dir.GoChild("EngineShader");
	std::vector<EngineFile> AllShaderFile = Dir.GetAllFile(".fx");

	for (EngineFile& ShaderFile : AllShaderFile)
	{
		std::string FileName = ShaderFile.GetFileName();

		EngineVertexShader* NewVertexShader = EngineVertexShader::CreateResource(FileName);
		NewVertexShader->CreateResourceWithDevice(FileName, ShaderFile.GetStringPath());

		EnginePixelShader* NewPixelShader = EnginePixelShader::CreateResource(FileName);
		NewPixelShader->CreateResourceWithDevice(FileName, ShaderFile.GetStringPath());

		D3D11_INPUT_ELEMENT_DESC Layouts[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		EngineInputLayout* NewInputLayout = EngineInputLayout::CreateResource("POSITION");
		NewInputLayout->CreateResourceWithDevice(Layouts[0], 1, NewVertexShader->GetShaderByteCode(), NewVertexShader->GetShaderByteLength());
	}

	std::string path = Dir.GetStringPath();

	{
		float4 Rect[] =
		{
			float4(-0.5f, 0.5f, 0.0f, 1.0f),
			float4(0.5f, 0.5f, 0.0f, 1.0f),
			float4(0.5f, -0.5f, 0.0f, 1.0f),
			float4(-0.5f, -0.5f, 0.0f, 1.0f)
		};
		EngineVertexBuffer* NewRes = EngineVertexBuffer::CreateResource("Rect");
		NewRes->CreateResourceWithDevice(Rect, sizeof(Rect));
	}

	{
		UINT Rect[]
		{
			0,1,2,
			0,2,3
		};
		EngineIndexBuffer* NewRes = EngineIndexBuffer::CreateResource("Rect");
		NewRes->CreateResourceWithDevice(Rect, sizeof(Rect));
	}
}