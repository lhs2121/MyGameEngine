#include "Pre.h"
#include "EnginePixelShader.h"
#include <fstream>
#include <iostream>
#include <d3dcompiler.h> // DirectX Shader Compiler

#pragma comment(lib, "d3dcompiler.lib")

EnginePixelShader::EnginePixelShader()
{
}

EnginePixelShader::~EnginePixelShader()
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

void EnginePixelShader::IntoPipeLine()
{
	m_pDevice->GetContext()->PSSetShader(ShaderPtr, nullptr, 0);
}
