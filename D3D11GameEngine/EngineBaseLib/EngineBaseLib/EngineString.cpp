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

	if (String == nullptr)
	{
		int ByteSize = GetByte(OtherString) + 1;

		if (ByteSize <= 16)
		{
			String = (char*)StringPool16.InsertObject((void*)OtherString, ByteSize);
		}
		else if (16 < ByteSize <= 32)
		{
			String = (char*)StringPool16.InsertObject((void*)OtherString, ByteSize);
		}
		else if (32 < ByteSize <= 64)
		{
			String = (char*)StringPool16.InsertObject((void*)OtherString, ByteSize);
		}
	}
	else
	{
		int ByteSize = GetByte() + 1;

		if (ByteSize <= 16)
		{
			StringPool16.DeleteObject(String);
			String = (char*)StringPool16.InsertObject((void*)OtherString, ByteSize);
		}
		else if (16 < ByteSize <= 32)
		{
			StringPool32.DeleteObject(String);
			String = (char*)StringPool16.InsertObject((void*)OtherString, ByteSize);
		}
		else if (32 < ByteSize <= 64)
		{
			StringPool64.DeleteObject(String);
			String = (char*)StringPool16.InsertObject((void*)OtherString, ByteSize);
		}
	}
}

void EngineString::operator+=(EngineString& OtherString)
{
	int ByteSize = OtherString.GetByte() + 1;

}

void EngineString::operator+=(const char* OtherString)
{
	int OtherSize = GetByte(OtherString) + 1;
	int ThisSize = GetByte();

	int ByteSize = OtherSize + ThisSize;

	if (ByteSize <= 16)
	{
		memcpy_s(String + ThisSize, OtherSize, OtherString, OtherSize);
	}
	else if (16 < ByteSize <= 32)
	{
		void* PrevPtr = String;

		String = (char*)StringPool32.InsertObject((void*)String, ThisSize + 1);
		memcpy_s(String + ThisSize, OtherSize, OtherString, OtherSize);

		StringPool16.DeleteObject(PrevPtr);
	}
	else if (32 < ByteSize <= 64)
	{
		StringPool64.DeleteObject(String);
		String = (char*)StringPool16.InsertObject((void*)OtherString, ByteSize);
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

