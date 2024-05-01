#include "Pre.h"
#include "EngineDevice.h"

void EngineDevice::ShaderInit()
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