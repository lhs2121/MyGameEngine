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

void EngineVertexShader::CreateResource(std::string _Name, std::string _Path)
{
	int Flag;
#ifdef _DEBUG
	// 11버전이 없다.
	// 에러 
	Flag = D3DCOMPILE_DEBUG;
#endif

	//std::string Include =
	//"float4 Value; \
	// float4 Pos; ";

	// 추후 상수버퍼 공부하면서 꼭 물어보세요
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
	ID3DBlob* ErrorBlob = nullptr;

	std::wstring Path = EngineString::GetWideString(_Path);

	std::string MainFuncName = _Name + "_VS";

	HRESULT Result = D3DCompileFromFile(Path.c_str(),
		nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, MainFuncName.c_str(), "vs_5_0", Flag, 0, &ShaderBlob, &ErrorBlob);

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

