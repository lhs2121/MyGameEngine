#include "Pre.h"
#include "EngineVertexShader.h"
#include <fstream>
#include <iostream>
#include <d3dcompiler.h> // DirectX Shader Compiler
#pragma comment(lib, "d3dcompiler.lib")

EngineVertexShader::EngineVertexShader()
{
}

EngineVertexShader::~EngineVertexShader()
{
	if (ShaderBlob != nullptr)
	{
		ShaderBlob->Release();
		ShaderBlob = nullptr;
	}

	if (ShaderPtr != nullptr)
	{
		ShaderPtr->Release();
		ShaderPtr = nullptr;
	}
}

void EngineVertexShader::IntoPipeLine()
{
	m_pDevice->GetContext()->VSSetShader(ShaderPtr, nullptr, 0);
}

void* EngineVertexShader::GetShaderByteCode()
{
	return ShaderBlob->GetBufferPointer();
}

SIZE_T EngineVertexShader::GetShaderByteLength()
{
	return ShaderBlob->GetBufferSize();
}

