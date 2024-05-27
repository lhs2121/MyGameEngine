#include "Pre.h"
#include "EngineString.h"

void* EngineString::FirstString16 = nullptr;
void* EngineString::FirstString32 = nullptr;
void* EngineString::FirstString64 = nullptr;

EngineString::EngineString()
{
}

EngineString::~EngineString()
{
	if (String != nullptr)
	{
		delete[] String;
		String = nullptr;
	}
}

void EngineString::operator=(EngineString& OtherString)
{
	int ByteSize = OtherString.GetByte();
	if (String == nullptr)
	{
		String = new char[ByteSize + 1];
	}
	else if(String != nullptr)
	{
		if (GetLen() < ByteSize)
		{
			delete[] String;
			String = new char[ByteSize + 1];
		}
		memset(String, 0, GetByte());
	}

	memcpy_s(String, ByteSize, OtherString.c_str(), ByteSize);
}

void EngineString::operator=(const char* OtherString)
{
	int ByteSize = GetByte(OtherString) + 1;
	if (String == nullptr)
	{
		if (ByteSize <= 16)
		{
			String = new char[16];
			if (FirstString16 == nullptr)
			{
				FirstString16 = String;
			}
		}
		else if (ByteSize <= 32)
		{
			String = new char[32];
			if (FirstString32 == nullptr)
			{
				FirstString32 = String;
			}
		}
		else if (ByteSize <= 64)
		{
			String = new char[64];
			if (FirstString64 == nullptr)
			{
				FirstString64 = String;
			}
		}
		
	}

	memcpy_s(String, ByteSize, OtherString, ByteSize);
}

void EngineString::GetUTF8(wchar_t** WideString)
{
	int WideByteSize = MultiByteToWideChar(CP_UTF8, 0, String, -1, NULL, 0);
	*WideString = new wchar_t[WideByteSize];
	MultiByteToWideChar(CP_UTF8, 0, String, -1, *WideString, WideByteSize);
}

int EngineString::GetByte(const char* OtherString)
{
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
			return Byte;
		}

		Index++;
	}
	return 0;
}

const char* EngineString::c_str()
{
	return String;
}

int EngineString::GetByte()
{
	int Index = 0;
	int Byte = 0;
	while (true)
	{
		char Ch = String[Index];
		if (Ch != '\0')
		{
			Byte++;
		}
		else
		{
			return Byte;
		}

		Index++;
	}
	return 0;
}

int EngineString::GetLen() const
{
	return (int)strlen(String);
}

void EngineString::operator+=(EngineString& OtherString)
{
	int ByteSize = OtherString.GetByte() + 1;

	if (String != nullptr)
	{
		int Len = GetByte() + ByteSize;
		if(Len)
		memcpy_s(String + Len, ByteSize, OtherString.c_str(), ByteSize);
	}
	else
	{
		*this = OtherString;
	}
}

void EngineString::operator+=(const char* OtherString)
{
	int OtherByte = GetByte(OtherString) + 1;

	if (String != nullptr)
	{
		int MyByte = GetByte();
		memcpy_s(String + MyByte, OtherByte, OtherString, OtherByte);
	}
	else
	{
		*this = OtherString;
	}
}
