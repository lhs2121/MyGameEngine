#include "Pre.h"
#include "EngineString.h"
#include "EngineBaseInterface.h"

bool EngineString::IsCreateStringPool = false;
IEngineStaticMemoryPool* EngineString::StringPool16 = nullptr;
IEngineStaticMemoryPool* EngineString::StringPool32 = nullptr;
IEngineStaticMemoryPool* EngineString::StringPool64 = nullptr;
IEngineStaticMemoryPool* EngineString::StringPool128 = nullptr;
IEngineStaticMemoryPool* EngineString::StringPool256 = nullptr;
IEngineStaticMemoryPool* EngineString::StringPool512 = nullptr;

EngineString::EngineString()
{
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
		IEngineStaticMemoryPool* CurPool = EngineString::GetStringPool(ByteSize);
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
		IEngineStaticMemoryPool* StringPool = EngineString::GetStringPool(PrevByteSize);
		memset(String, 0, PrevByteSize);
		StringPool->FreeBlock(String);
	}

	// 인자문자열의 바이트에 적합한 메모리풀 블록을 가져온다
	int ByteSize = GetByte(OtherString);
	IEngineStaticMemoryPool* StringPool = EngineString::GetStringPool(ByteSize);
	String = (char*)StringPool->GetBlock();

	memcpy_s(String, ByteSize, OtherString, ByteSize);
}

void EngineString::operator+=(EngineString& OtherString)
{
	*this += OtherString.c_str();
}

void EngineString::operator+=(const char* OtherString)
{
	int Byte = EngineString::GetByte(String);
	if (Byte != 0)
	{
		--Byte;
	}
	int OtherByte = EngineString::GetByte(OtherString);
	char* TempString = new char[Byte + OtherByte];

	if (String != nullptr)
	{
		memcpy_s(TempString, Byte, String, Byte);
		memcpy_s(TempString + Byte, OtherByte, OtherString, OtherByte);
	}
	else
	{
		memcpy_s(TempString, OtherByte, OtherString, OtherByte);
	}

	*this = TempString;

	delete[] TempString;
	TempString = nullptr;
}

void EngineString::operator+=(unsigned long long Num)
{
	int DigitCount = EngineMath::GetDigitCount(Num);
	char* ConvertString = new char[DigitCount + 1];
	
	sprintf_s(ConvertString, DigitCount + 1, "%llu", Num);

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
	else
	{
		return false;
	}
}

bool EngineString::operator!=(EngineString& OtherString)
{
	int ByteSize = EngineString::GetByte(String);
	int Result = strncmp(String, OtherString.String, ByteSize);
	if (Result == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool EngineString::operator!=(const char* OtherString)
{
	int ByteSize = EngineString::GetByte(String);
	int Result = strncmp(String, OtherString, ByteSize);
	if (Result == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void EngineString::GetUTF8(wchar_t** WideString)
{
	int WideByteSize = MultiByteToWideChar(CP_UTF8, 0, String, -1, NULL, 0);
	*WideString = new wchar_t[WideByteSize];
	MultiByteToWideChar(CP_UTF8, 0, String, -1, *WideString, WideByteSize);
}

int EngineString::GetByte(const char* OtherString)
{
	return (int)strlen(OtherString) + 1;
}

const char* EngineString::c_str()
{
	return String;
}

IEngineStaticMemoryPool* EngineString::GetStringPool(int ByteSize)
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

	EngineDebug::MsgBoxAssert("바이트가 너무 큰데?");
	
}

void EngineString::CreateAllStringPool()
{
	CreateEngineStaticMemoryPool(&StringPool16);
	StringPool16->Init(16 * 100000, 16);


	CreateEngineStaticMemoryPool(&StringPool32);
	StringPool32->Init(32 * 100000, 32);


	CreateEngineStaticMemoryPool(&StringPool64);
	StringPool64->Init(64 * 100000, 64);


	CreateEngineStaticMemoryPool(&StringPool128);
	StringPool128->Init(128 * 5000, 128);


	CreateEngineStaticMemoryPool(&StringPool256);
	StringPool256->Init(256 * 5000, 256);


	CreateEngineStaticMemoryPool(&StringPool512);
	StringPool512->Init(512 * 5000, 512);

	IsCreateStringPool = true;
}

void EngineString::DeleteAllStringPool()
{
	if (IsCreateStringPool == false)
	{
		return;
	}

	DeleteEngineStaticMemoryPool(StringPool16);
	StringPool16 = nullptr;

	DeleteEngineStaticMemoryPool(StringPool32);
	StringPool16 = nullptr;

	DeleteEngineStaticMemoryPool(StringPool64);
	StringPool16 = nullptr;

	DeleteEngineStaticMemoryPool(StringPool128);
	StringPool128 = nullptr;


	DeleteEngineStaticMemoryPool(StringPool256);
	StringPool256 = nullptr;

	DeleteEngineStaticMemoryPool(StringPool512);
	StringPool512 = nullptr;

	IsCreateStringPool = false;
}