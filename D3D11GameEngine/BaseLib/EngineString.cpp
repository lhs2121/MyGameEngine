#include "Pre.h"
#include "EngineString.h"
#include "BaseAPI.h"

bool EngineString::IsCreateStringPool = false;
IEngineStaticPool* EngineString::StringPool16 = nullptr;
IEngineStaticPool* EngineString::StringPool32 = nullptr;
IEngineStaticPool* EngineString::StringPool64 = nullptr;
IEngineStaticPool* EngineString::StringPool128 = nullptr;
IEngineStaticPool* EngineString::StringPool256 = nullptr;
IEngineStaticPool* EngineString::StringPool512 = nullptr;

EngineString::EngineString()
{
}

bool EngineString::operator<(const EngineString& other) const
{
	return strcmp(String, other.String) < 0;
}

EngineString::~EngineString()
{
	if (String != nullptr)
	{
		if (IsCreateStringPool == false)
		{
			String = nullptr;
			return;
		}

		int ByteSize = GetByte(String);
		IEngineStaticPool* CurPool = EngineString::GetStringPool(ByteSize);
		memset(String, 0, ByteSize);
		CurPool->FreeBlock(String);
		String = nullptr;
	}
}

void EngineString::operator=(EngineString& OtherString)
{
	*this = OtherString.c_str();
}

void EngineString::operator=(const char* OtherString)
{
	// 메모리풀이 없다면 생성해주고
	if (IsCreateStringPool == false)
	{
		EngineString::CreateAllStringPool();
	}

	// 이미 문자열이있다면 제거해주고
	if (String != nullptr)
	{
		int PrevByteSize = EngineString::GetByte(String);
		IEngineStaticPool* StringPool = EngineString::GetStringPool(PrevByteSize);
		memset(String, 0, PrevByteSize);
		StringPool->FreeBlock(String);
	}

	// 인자문자열의 바이트에 적합한 메모리풀 블록을 가져온다
	int ByteSize = GetByte(OtherString);
	IEngineStaticPool* StringPool = EngineString::GetStringPool(ByteSize);
	String = (char*)StringPool->GetBlock();

	memcpy_s(String, ByteSize, OtherString, ByteSize);
}

void EngineString::operator+=(EngineString& OtherString)
{
	*this += OtherString.c_str();
}

void EngineString::operator+=(const char* OtherString)
{
	int ByteSize = 0;
	if (String != nullptr)
	{
		ByteSize = EngineString::GetByte(String);
		--ByteSize;
	}
	int OtherByte = EngineString::GetByte(OtherString);
	char* TempString = new char[ByteSize + OtherByte];

	if (String != nullptr)
	{
		memcpy_s(TempString, ByteSize, String, ByteSize);
		memcpy_s(TempString + ByteSize, OtherByte, OtherString, OtherByte);
	}
	else
	{
		memcpy_s(TempString, OtherByte, OtherString, OtherByte);
	}

	*this = TempString;

	delete[] TempString;
	TempString = nullptr;
}

void EngineString::operator+=(double Num)
{
	char* ConvertString = new char[20];
	
	sprintf_s(ConvertString, 20, "%lf", Num);

	if (String != nullptr)
	{
		*this += ConvertString;
	}
	else
	{
		*this = ConvertString;
	}

	if (ConvertString != nullptr)
	{
		delete[] ConvertString;
		ConvertString = nullptr;
	}
}


bool EngineString::operator==(EngineString& OtherString)
{
	int ByteSize = EngineString::GetByte(String);
	int Result = strncmp(String, OtherString.String, ByteSize);
	if (Result == 0)
	{
		return true;
	}

	return false;
}

bool EngineString::operator==(const char* OtherString)
{
	int ByteSize = EngineString::GetByte(String);
	int Result = strncmp(String, OtherString, ByteSize);
	if (Result == 0)
	{
		return true;
	}

	return false;
}

bool EngineString::operator!=(EngineString& OtherString)
{
	int ByteSize = EngineString::GetByte(String);
	int Result = strncmp(String, OtherString.String, ByteSize);
	if (Result == 0)
	{
		return false;
	}

	return true;
}

bool EngineString::operator!=(const char* OtherString)
{
	int ByteSize = EngineString::GetByte(String);

	if (String == 0 && OtherString == 0)
	{
		return false;
	}

	if (String != 0 && OtherString == 0)
	{
		return true;
	}

	if (String == 0 && OtherString != 0)
	{
		return true;
	}

	int Result = strncmp(String, OtherString, ByteSize);
	if (Result == 0)
	{
		return false;
	}

	return true;
}

void EngineString::GetUTF8(wchar_t** WideString)
{
	int WideByteSize = MultiByteToWideChar(CP_UTF8, 0, String, -1, NULL, 0);
	*WideString = new wchar_t[WideByteSize];
	MultiByteToWideChar(CP_UTF8, 0, String, -1, *WideString, WideByteSize);
}

int EngineString::GetByte(const char* OtherString)
{
	if (OtherString == nullptr)
	{
		return 0;
	}

	return (int)strlen(OtherString) + 1;
}

const char* EngineString::c_str()
{
	return String;
}

IEngineStaticPool* EngineString::GetStringPool(int ByteSize)
{
	if (ByteSize <= 16)
	{
		return StringPool16;
	}
	else if (ByteSize > 16 && ByteSize <= 32)
	{
		return StringPool32;
	}
	else if (ByteSize > 32 && ByteSize <= 64)
	{
		return StringPool64;
	}
	else if (ByteSize > 64 && ByteSize <= 128)
	{
		return StringPool128;
	}
	else if (ByteSize > 128 && ByteSize <= 256)
	{
		return StringPool256;
	}
	else if (ByteSize > 256 && ByteSize <= 512)
	{
		return StringPool512;
	}
	else
	{
		EngineDebug::MsgBoxAssert("바이트가 너무 큰데?");
		return nullptr;
	}
	
	
}

void EngineString::CreateAllStringPool()
{
	CreateEngineStaticPool(&StringPool16);
	StringPool16->Init(1000, 16);


	CreateEngineStaticPool(&StringPool32);
	StringPool32->Init(1000, 32);


	CreateEngineStaticPool(&StringPool64);
	StringPool64->Init(1000, 64);


	CreateEngineStaticPool(&StringPool128);
	StringPool128->Init(500, 128);


	CreateEngineStaticPool(&StringPool256);
	StringPool256->Init(500, 256);


	CreateEngineStaticPool(&StringPool512);
	StringPool512->Init(500, 512);

	IsCreateStringPool = true;
}

void EngineString::DeleteAllStringPool()
{
	if (IsCreateStringPool == false)
	{
		return;
	}

	DeleteEngineStaticPool(StringPool16);
	StringPool16 = nullptr;

	DeleteEngineStaticPool(StringPool32);
	StringPool16 = nullptr;

	DeleteEngineStaticPool(StringPool64);
	StringPool16 = nullptr;

	DeleteEngineStaticPool(StringPool128);
	StringPool128 = nullptr;


	DeleteEngineStaticPool(StringPool256);
	StringPool256 = nullptr;

	DeleteEngineStaticPool(StringPool512);
	StringPool512 = nullptr;

	IsCreateStringPool = false;
}