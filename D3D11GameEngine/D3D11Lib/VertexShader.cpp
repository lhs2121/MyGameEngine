#include "Pre.h"
#include "VertexShader.h"

VertexShader::VertexShader()
{
}

VertexShader::~VertexShader()
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

EngineString VertexShader::GetLayoutName()
{
	EngineString Result;
	
	size_t Size = Sementics.size();
	for (size_t i = 0; i < Size; i++)
	{
		Result += Sementics[i];

		if (i == Size - 1)
		{
			break;
		}
		Result += "_";

	}
	return Result;
}

UINT VertexShader::GetSlotNumber(const char* _BindingResName)
{
	ShaderFile.Move(_BindingResName);
	ShaderFile.Move("register(",MoveMode::End);
	ShaderFile.MoveNext();
	ShaderFile.MoveNext();


	char SlotNumber = ShaderFile.GetChar();
	return (UINT)(atoi(&SlotNumber));
}

void VertexShader::Setting( EngineString _Name, EngineString _Path)
{
	ShaderFile.SetPath(_Path.c_str());
	ShaderFile.ReadFileToMemory();
	ShaderFile.Move("struct");
	ShaderFile.Move("VS_INPUT");
	while (true)
	{
		ShaderFile.Move(":");
		ShaderFile.MoveNext();
		ShaderFile.MoveNext();
		EngineString Sementic = ShaderFile.GetString(';');

		Sementics.push_back(Sementic);

		ShaderFile.Move("\n");
		ShaderFile.MoveNext();
		char End = ShaderFile.GetChar();
		if (End == '}')
		{
			break;
		}


	}

	EngineString MainFuncName = _Name;
	MainFuncName += "_VS";

	wchar_t* UTF8Path;
	_Path.GetUTF8(&UTF8Path);

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

void VertexShader::IntoPipeline()
{
	ContextPtr->VSSetShader(ShaderPtr, nullptr, 0);
}

void* VertexShader::GetShaderByteCode()
{
	return BlobPtr->GetBufferPointer();
}

SIZE_T VertexShader::GetShaderByteLength()
{
	return BlobPtr->GetBufferSize();
}

