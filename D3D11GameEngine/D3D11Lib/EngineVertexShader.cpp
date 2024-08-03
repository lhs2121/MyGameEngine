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

EngineString EngineVertexShader::GetSementic()
{
	FILE* f;
	fopen_s(&f, Path.c_str(), "r");

	EngineString ReturnString;
	const char* searchstring = "VS_INPUT";
	int len = strlen(searchstring);

	char* SemanticBuffer = nullptr;
	int combo = 0;
	while (true)
	{
		char c = fgetc(f);
		if (c == '\n' || c == ' ')
		{
			continue;
		}

		if (combo != len)
		{
			if (searchstring[combo] == c)
			{
				combo += 1;
			}
			else
			{
				combo = 0;
			}
		}

		if (combo == len)
		{
			if (c == '}')
			{
				break;
			}

			if (c == ':')
			{
				SemanticBuffer = new char[32];
				int index = 0;

				while (true)
				{
					char b = fgetc(f);
					if (b == ' ')
					{
						continue;
					}

					if (b == ';')
					{
						SemanticBuffer[index] = '\0';
						ReturnString += SemanticBuffer;

						fseek(f, 2, SEEK_CUR);
						char d = fgetc(f);
						if (d != '}')
						{
							ReturnString += "_";
							break;
						}

						return ReturnString;
					}

					SemanticBuffer[index] = b;
					index++;
				}
			}
		}
	}

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

