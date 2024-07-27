#include "Pre.h"
#include "EnginePixelShader.h"

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

void EnginePixelShader::Setting(EngineString _Name, EngineString _Path)
{
	EngineString MainFuncName = _Name;
	MainFuncName += "_PS";
	wchar_t* UTF8Path;
	EngineString PathString = _Path;
	PathString.GetUTF8(&UTF8Path);

	int Flag;

#ifdef _DEBUG
	Flag = D3DCOMPILE_DEBUG;

#endif
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;


	ID3DBlob* ErrorBlob = nullptr;

	HRESULT Result = D3DCompileFromFile(UTF8Path,
		nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, MainFuncName.c_str(), "ps_5_0", Flag, 0, &ShaderBlob, &ErrorBlob);


	if (FAILED(Result))
	{
		if (ErrorBlob)
		{
			OutputDebugStringA(static_cast<const char*>(ErrorBlob->GetBufferPointer()));
			ErrorBlob->Release();
		}
	}

	DevicePtr->CreatePixelShader(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), nullptr, &ShaderPtr);

	if (UTF8Path != nullptr)
	{
		delete[] UTF8Path;
		UTF8Path = nullptr;
	}
}

void EnginePixelShader::IntoPipeLine()
{
	ContextPtr->PSSetShader(ShaderPtr, nullptr, 0);
}

