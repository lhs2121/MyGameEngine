#include "Pre.h"
#include "EngineVertexShader.h"

EngineVertexShader::EngineVertexShader()
{
}

EngineVertexShader::~EngineVertexShader()
{
	if (BlobPtr != nullptr)
	{
		BlobPtr->Release();
		BlobPtr = nullptr;
	}

	if (ShaderPtr != nullptr)
	{
		ShaderPtr->Release();
		ShaderPtr = nullptr;
	}
}

SementicInfo* EngineVertexShader::SetSementicInfo()
{
	InfoArray = new SementicInfo[16];
	char** SementicNames = new char*[8];
	for (size_t i = 0; i < 6; i++)
	{
		SementicNames[i] = new char[64];
	}

	FILE* f;
	fopen_s(&f, Path.c_str(), "r");


}

void EngineVertexShader::Setting(EngineString _Name, EngineString _Path)
{
	Path = _Path;
	EngineString MainFuncName = _Name;
	MainFuncName += "_VS";

	EngineString PathString = Path;
	wchar_t* UTF8Path;
	PathString.GetUTF8(&UTF8Path);

	int Flag;

#ifdef _DEBUG
	Flag = D3DCOMPILE_DEBUG;

#endif
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	ID3DBlob* ErrorBlob = nullptr;



	HRESULT Result = D3DCompileFromFile(UTF8Path,
		nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, MainFuncName.c_str(), "vs_5_0", Flag, 0, &BlobPtr, &ErrorBlob);

	if (FAILED(Result))
	{
		if (ErrorBlob)
		{
			OutputDebugStringA(static_cast<const char*>(ErrorBlob->GetBufferPointer()));
			ErrorBlob->Release();
		}
	}

	HRESULT R = DevicePtr->CreateVertexShader(BlobPtr->GetBufferPointer(), BlobPtr->GetBufferSize(), nullptr, &ShaderPtr);

	if (UTF8Path != nullptr)
	{
		delete[] UTF8Path;
		UTF8Path = nullptr;
	}
}

void EngineVertexShader::IntoPipeline()
{
	ContextPtr->VSSetShader(ShaderPtr, nullptr, 0);
}

void* EngineVertexShader::GetShaderByteCode()
{
	return BlobPtr->GetBufferPointer();
}

SIZE_T EngineVertexShader::GetShaderByteLength()
{
	return BlobPtr->GetBufferSize();
}

