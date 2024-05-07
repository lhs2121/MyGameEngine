#include "Pre.h"
#include "EnginePixelShader.h"
#include <fstream>
#include <d3dcompiler.h> 

#pragma comment(lib, "d3dcompiler.lib")

EnginePixelShader::EnginePixelShader()
{
}

EnginePixelShader::~EnginePixelShader()
{
}

void EnginePixelShader::Setting(const char* _Name, const char* _Path)
{
	std::string MainFuncName = _Name;
	MainFuncName += "_PS";

	std::string PathString = _Path;
	std::wstring WPathString = EngineString::GetWideString(PathString);

	int Flag;

#ifdef _DEBUG
	Flag = D3DCOMPILE_DEBUG;

#endif
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;


	ID3DBlob* ErrorBlob = nullptr;

	HRESULT Result = D3DCompileFromFile(WPathString.c_str(),
		nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, MainFuncName.c_str(), "ps_5_0", Flag, 0, &ShaderBlob, &ErrorBlob);


	if (FAILED(Result))
	{
		if (ErrorBlob)
		{
			OutputDebugStringA(static_cast<const char*>(ErrorBlob->GetBufferPointer()));
			ErrorBlob->Release();
		}
	}

	DevicePtr->GetDevice()->CreatePixelShader(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), nullptr, &ShaderPtr);
}

void EnginePixelShader::Release()
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
	DevicePtr->GetContext()->PSSetShader(ShaderPtr, nullptr, 0);
}

