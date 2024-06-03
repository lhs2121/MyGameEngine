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
	if (String != nullptr)
	{
		int ByteSize = GetByte(String);
		if (ByteSize <= 16)
		{
			StringPool16.DeleteObject(String);
		}
		else if (16 < ByteSize <= 32)
		{
			StringPool32.DeleteObject(String);
		}
		else if (32 < ByteSize <= 64)
		{
			StringPool64.DeleteObject(String);
		}

		String = nullptr;
	}
}

void EngineString::operator=(EngineString& OtherString)
{
	*this = OtherString.c_str();
}

void EngineString::operator=(const char* OtherString)
{
	// �޸�Ǯ�� �ִ��� üũ
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

	// �̹� ���ڿ����ִٸ� �������ְ�
	if (String != nullptr)
	{
		int PrevByteSize = GetByte(String);
	    EngineMemoryPool* StringPool =  GetStringPool(PrevByteSize);

		StringPool->DeleteObject(String);
	}

	// ���ڹ��ڿ��� ����Ʈ�� ������ �޸�Ǯ ����� �����´�
	int ByteSize = GetByte(OtherString);
	EngineMemoryPool* StringPool = GetStringPool(ByteSize);
	String = (char*)StringPool->GetBlock();

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

EngineMemoryPool* EngineString::GetStringPool(int ByteSize)
{
	if (ByteSize <= 16)
	{
		return &StringPool16;
	}
	else if (16 < ByteSize <= 32)
	{
		return &StringPool32;
	}
	else if (32 < ByteSize <= 64)
	{
		return &StringPool64;
	}
}