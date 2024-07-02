#include "Pre.h"
#include "EngineString.h"
#include "EngineBaseInterface.h"

bool EngineString::IsCreateStringPool = false;
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
		if (IsCreateStringPool == false)
		{
			String = nullptr;
			return;
		}

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
	// 메모리풀이 없다면 생성해주고
	if (IsCreateStringPool == false)
	{
		EngineString::CreateAllStringPool();
	}

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
	return (int)strlen(OtherString) + 1;
}

const char* EngineString::c_str()
{
	return String;
}

IEngineMemoryPool* EngineString::GetStringPool(int ByteSize)
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
	CreateEngineMemoryPool(&StringPool16);
	StringPool16->Init(16 * 100000, 16);


	CreateEngineMemoryPool(&StringPool32);
	StringPool32->Init(32 * 100000, 32);


	CreateEngineMemoryPool(&StringPool64);
	StringPool64->Init(64 * 100000, 64);


	CreateEngineMemoryPool(&StringPool128);
	StringPool128->Init(128 * 5000, 128);


	CreateEngineMemoryPool(&StringPool256);
	StringPool256->Init(256 * 5000, 256);


	CreateEngineMemoryPool(&StringPool512);
	StringPool512->Init(512 * 5000, 512);

	IsCreateStringPool = true;
}

void EngineString::DeleteAllStringPool()
{
	if (IsCreateStringPool == false)
	{
		return;
	}

	DeleteEngineMemoryPool(StringPool16);
	StringPool16 = nullptr;

	DeleteEngineMemoryPool(StringPool32);
	StringPool16 = nullptr;

	DeleteEngineMemoryPool(StringPool64);
	StringPool16 = nullptr;

	DeleteEngineMemoryPool(StringPool128);
	StringPool128 = nullptr;


	DeleteEngineMemoryPool(StringPool256);
	StringPool256 = nullptr;

	DeleteEngineMemoryPool(StringPool512);
	StringPool512 = nullptr;

	IsCreateStringPool = false;
}