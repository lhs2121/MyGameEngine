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

void EnginePixelShader::CreateResource(std::string _Name, std::string _Path)
{
	int Flag;
#ifdef _DEBUG
	Flag = D3DCOMPILE_DEBUG;
#endif
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	std::string MainFuncName = _Name + "_PS";
	ID3DBlob* ErrorBlob = nullptr;
	HRESULT Result = D3DCompileFromFile(L"F:\\MyGameEngine\\D3D11GameEngine\\EngineShader\\TestShader.fx",
		nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, MainFuncName.c_str(), "ps_5_0", Flag, 0, &ShaderBlob, &ErrorBlob);

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

