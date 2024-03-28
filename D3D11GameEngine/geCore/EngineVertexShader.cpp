#include "Pre.h"
#include "EngineVertexShader.h"


EngineVertexShader::EngineVertexShader()
{
}

EngineVertexShader::~EngineVertexShader()
{
	if (ShaderPtr != nullptr)
	{
		delete ShaderPtr;
		ShaderPtr = nullptr;
	}
}

void EngineVertexShader::SetResource()
{
	//HRESULT Result = EngineCore::GetDevice()->CreateVertexShader()
}

void EngineVertexShader::IntoPipeLine()
{
	//EngineCore::GetContext()->VSSetShader()
}
