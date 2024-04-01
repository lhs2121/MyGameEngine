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
	if (ShaderPtr != nullptr)
	{
		delete ShaderPtr;
		ShaderPtr = nullptr;
	}
}

void EnginePixelShader::ShaderLoad(std::string _Name, std::string _Path)
{
	std::string MainFuncName = _Name + "_PS";
	std::fstream shaderFile(_Path);

	shaderFile.seekg(0, std::ios::end);
	unsigned long long FileSize = shaderFile.tellg();
	shaderFile.seekg(0, std::ios::beg);


	std::vector<char> shaderData;
	shaderData.resize(FileSize);

	shaderFile.read(shaderData.data(), FileSize);

	ID3DBlob* ErrorBlob = nullptr;

	HRESULT Result = D3DCompile(shaderData.data(), FileSize, _Path.c_str(), nullptr, nullptr, MainFuncName.c_str(), "ps_5_0", 0, 0, &ShaderBlob, &ErrorBlob);
	if (FAILED(Result))
	{
		if (ErrorBlob)
		{
			OutputDebugStringA(static_cast<const char*>(ErrorBlob->GetBufferPointer()));
			ErrorBlob->Release();
		}
	}
	EngineCore::GetDevice()->CreatePixelShader(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), nullptr, &ShaderPtr);

	
}

void EnginePixelShader::IntoPipeLine()
{
	EngineCore::GetContext()->PSSetShader(ShaderPtr, nullptr, 0);
}
