#include "Pre.h"
#include "EngineVertexShader.h"

EngineVertexShader::EngineVertexShader()
{
}

EngineVertexShader::~EngineVertexShader()
{
}

void EngineVertexShader::Setting(EngineString _Name, EngineString _Path)
{
	EngineString MainFuncName = _Name;
	MainFuncName += "_VS";

	EngineString PathString = _Path;
	wchar_t* UTF8Path;
	PathString.GetUTF8(&UTF8Path);

	int Flag;

#ifdef _DEBUG
	Flag = D3DCOMPILE_DEBUG;

#endif
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	ID3DBlob* ErrorBlob = nullptr;



	HRESULT Result = D3DCompileFromFile(UTF8Path,
		nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, MainFuncName.c_str(), "vs_5_0", Flag, 0, &ShaderBlob, &ErrorBlob);

	if (FAILED(Result))
	{
		if (ErrorBlob)
		{
			OutputDebugStringA(static_cast<const char*>(ErrorBlob->GetBufferPointer()));
			ErrorBlob->Release();
		}
	}

	HRESULT R = DevicePtr->GetDevice()->CreateVertexShader(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), nullptr, &ShaderPtr);

	if (UTF8Path != nullptr)
	{
		delete[] UTF8Path;
		UTF8Path = nullptr;
	}
}

void EngineVertexShader::Release()
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
	DevicePtr->GetContext()->VSSetShader(ShaderPtr, nullptr, 0);
}

void* EngineVertexShader::GetShaderByteCode()
{
	return ShaderBlob->GetBufferPointer();
}

SIZE_T EngineVertexShader::GetShaderByteLength()
{
	return ShaderBlob->GetBufferSize();
}

