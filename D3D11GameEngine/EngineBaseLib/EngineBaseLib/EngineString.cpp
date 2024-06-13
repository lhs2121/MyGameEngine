#include "Pre.h"
#include "EngineString.h"
#include "IEngineBase.h"

IEngineMemoryPool* EngineString::StringPool16 = nullptr;
IEngineMemoryPool* EngineString::StringPool32 = nullptr;
IEngineMemoryPool* EngineString::StringPool64 = nullptr;
IEngineMemoryPool* EngineString::StringPool128 = nullptr;
IEngineMemoryPool* EngineString::StringPool256 = nullptr;
IEngineMemoryPool* EngineString::StringPool512 = nullptr;
EngineString::EngineString()
{
}

EngineString::~EngineString()
{
	if (String != nullptr)
	{
		int ByteSize = GetByte(String);
		IEngineMemoryPool* CurPool = EngineString::GetStringPool(ByteSize);
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
	// 이미 문자열이있다면 제거해주고
	if (String != nullptr)
	{
		int PrevByteSize = EngineString::GetByte(String);
	    IEngineMemoryPool* StringPool = EngineString::GetStringPool(PrevByteSize);
		memset(String, 0, PrevByteSize);
		StringPool->FreeBlock(String);
	}

	// 인자문자열의 바이트에 적합한 메모리풀 블록을 가져온다
	int ByteSize = GetByte(OtherString);
	IEngineMemoryPool* StringPool = EngineString::GetStringPool(ByteSize);
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

bool EngineString::operator==(EngineString& OtherString)
{
	int ByteSize = EngineString::GetByte(String);
	int Result = strncmp(String, OtherString.String, ByteSize);
	if (Result == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
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
	if (OtherString == nullptr)
	{
		return 0;
	}

	int Index = 0;
	int Byte = 0;
	while (true)
	{
		char Ch = OtherString[Index];
		if (Ch != '\0')
		{
			Byte++;
		}
		else
		{
			return Byte + 1;
		}

		Index++;
	}
}

const char* EngineString::c_str()
{
	return String;
}

IEngineMemoryPool* EngineString::GetStringPool(int ByteSize)
{
	// 메모리풀이 있는지 체크
	if (StringPool16 == nullptr)
	{
		CreateMemoryPool(&StringPool16);
		StringPool16->Init(16 * 1000, 16);
	}
	if (StringPool32 == nullptr)
	{
		CreateMemoryPool(&StringPool32);
		StringPool32->Init(32 * 1000, 32);
	}
	if (StringPool64 == nullptr)
	{
		CreateMemoryPool(&StringPool64);
		StringPool64->Init(64 * 1000, 64);
	}
	if (StringPool128 == nullptr)
	{
		CreateMemoryPool(&StringPool128);
		StringPool128->Init(128 * 100, 128);
	}
	if (StringPool256 == nullptr)
	{
		CreateMemoryPool(&StringPool256);
		StringPool256->Init(256 * 10, 256);
	}
	if (StringPool512 == nullptr)
	{
		CreateMemoryPool(&StringPool512);
		StringPool512->Init(512 * 10, 512);
	}

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
		return nullptr;
	}
}