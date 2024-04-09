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
	if (ShaderPtr != nullptr)
	{
		delete ShaderPtr;
		ShaderPtr = nullptr;
	}
}

void EngineVertexShader::ShaderLoad(std::string _Name, std::string _Path)
{
	std::string MainFuncName = _Name + "_VS";
	std::fstream shaderFile(_Path);

	shaderFile.seekg(0, std::ios::end);
	unsigned long long FileSize = shaderFile.tellg();
	shaderFile.seekg(0, std::ios::beg);


	std::vector<char> shaderData;
	shaderData.resize(FileSize);

	shaderFile.read(shaderData.data(), FileSize);

	ID3DBlob* ErrorBlob = nullptr;

	HRESULT Result = D3DCompile(shaderData.data(), FileSize, _Path.c_str(), nullptr, nullptr, MainFuncName.c_str(), "vs_5_0", 0, 0, &ShaderBlob, &ErrorBlob);
	if (FAILED(Result))
	{
		if (ErrorBlob)
		{
			OutputDebugStringA(static_cast<const char*>(ErrorBlob->GetBufferPointer()));
			ErrorBlob->Release();
		}
	}

	EngineCore::GetDevice()->CreateVertexShader(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), nullptr, &ShaderPtr);
}

void EngineVertexShader::IntoPipeLine()
{
	EngineCore::GetContext()->VSSetShader(ShaderPtr, nullptr, 0);
}

void* EngineVertexShader::GetShaderByteCode()
{
	return ShaderBlob->GetBufferPointer();
}

SIZE_T EngineVertexShader::GetShaderByteLength()
{
	return ShaderBlob->GetBufferSize();
}
