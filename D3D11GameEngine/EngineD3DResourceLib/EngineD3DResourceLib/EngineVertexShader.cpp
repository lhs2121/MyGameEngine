#include "Pre.h"
#include "EngineVertexShader.h"

EngineVertexShader::EngineVertexShader()
{
}

EngineVertexShader::~EngineVertexShader()
{
}

void EngineVertexShader::Setting(const char* _Name, const char* _Path)
{
	std::string MainFuncName = _Name;
	MainFuncName += "_VS";

	std::string PathString = _Path;
	std::wstring WPathString = EngineString::GetWideString(PathString);

	int Flag;

#ifdef _DEBUG
	Flag = D3DCOMPILE_DEBUG;

#endif
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	ID3DBlob* ErrorBlob = nullptr;



	HRESULT Result = D3DCompileFromFile(WPathString.c_str(),
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

