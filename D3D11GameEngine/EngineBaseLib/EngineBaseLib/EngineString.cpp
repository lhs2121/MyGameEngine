#include "Pre.h"
#include "EngineString.h"

EngineMemoryPool EngineString::StringPool16;
EngineMemoryPool EngineString::StringPool32;
EngineMemoryPool EngineString::StringPool64;

EngineString::EngineString()
{
}

EngineString::~EngineString()
{
}

void EngineString::operator=(EngineString& OtherString)
{
	*this = OtherString.c_str();
}

void EngineString::operator=(const char* OtherString)
{
	// 메모리풀이 있는지 체크
	if (StringPool16.IsUsing() == false)
	{
		StringPool16.CreatePool(1024, 16);
	}
	if (StringPool32.IsUsing() == false)
	{
		StringPool32.CreatePool(1024, 32);
	}
	if (StringPool64.IsUsing() == false)
	{
		StringPool64.CreatePool(1024, 64);
	}

	// 이미 문자열이있다면 제거해주고
	if (String != nullptr)
	{
		int PrevByteSize = GetByte(String);
		if (PrevByteSize <= 16)
		{
			StringPool16.DeleteObject(String);
		}
		else if (16 < PrevByteSize <= 32)
		{
			StringPool32.DeleteObject(String);
		}
		else if (32 < PrevByteSize <= 64)
		{
			StringPool64.DeleteObject(String);
		}
	}

	// 인자문자열의 바이트에 적합한 메모리풀 블록을 가져온다
	int ByteSize = GetByte(OtherString);

	if (ByteSize <= 16)
	{
		String = (char*)StringPool16.GetBlock();
	}
	else if (16 < ByteSize <= 32)
	{
		String = (char*)StringPool32.GetBlock();
	}
	else if (32 < ByteSize <= 64)
	{
		String = (char*)StringPool64.GetBlock();
	}

	memcpy_s(String, ByteSize, OtherString, ByteSize);
}

void EngineString::operator+=(EngineString& OtherString)
{
	*this += OtherString.c_str();
}

void EngineString::operator+=(const char* OtherString)
{
	int Byte = GetByte(String);
	if (Byte != 0)
	{
		--Byte;
	}
	int OtherByte = GetByte(OtherString);
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

int EngineString::GetLen() const
{
	return (int)strlen(String);
}

